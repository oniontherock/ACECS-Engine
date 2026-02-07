# ACECS Engine — Application-Centric Entity Component System

ACECS Engine is a modular **C++17** ECS framework for building games and simulations. It provides an **Entity–Component–System** core, an **event** mechanism, **panel-based rendering**, **input mapping**, **game states**, **level/world management**, and a **save/load** framework—built on **SFML 3.0.0** (headers + `.lib` files are included in this repo).

This repository is the **engine/framework code + example “User” layer**. It does **not** include a standalone executable or a `main()`—you integrate ACECS into your own application and provide the entry point / game loop.

---

## Contents

- [Repo structure](#repo-structure)
- [Modules at a glance](#modules-at-a-glance)
- [Core concepts](#core-concepts)
  - [ECS](#ecs)
  - [Events](#events)
  - [World / Levels](#world--levels)
  - [Panels (Rendering)](#panels-rendering)
  - [Input](#input)
  - [Game States](#game-states)
  - [Saving / Loading](#saving--loading)
- [Using ACECS in your own app](#using-acecs-in-your-own-app)
  - [Include paths](#include-paths)
  - [Linking SFML](#linking-sfml)
  - [Minimal `main()` example](#minimal-main-example)
- [Example “User” layer](#example-user-layer)
- [Notes](#notes)

---

## Repo structure

```
ACECS-Engine/
├─ Engine Modules/
│  ├─ ECS/            # entities, components, events, pooling, type IDs
│  ├─ World/          # level grid, base level, updater, positions
│  ├─ Graphics/       # window holder, panels, panel manager, image/texture stores
│  ├─ Input/          # input interface, key recorder, input events
│  ├─ GameState/      # game state handler + transitions
│  ├─ Saving/         # save handler + save director
│  ├─ Audio/          # audio stores + playback helpers
│  ├─ Auxiliary/      # RNG, math, time, cooldown, console logging, stores
│  ├─ User/           # example wiring: engine lifecycle + registries + example states/panels
│  ├─ ECS.hpp / Graphics.hpp / Input.hpp / World.hpp / GameState.hpp / Audio.hpp
│  └─ ...
├─ SFMLInclude/       # bundled SFML headers (SFML 3.0.0)
└─ SFMLLib/           # bundled SFML + dependency .lib files (static + non-static variants)
```

---

## Modules at a glance

ACECS is split into modules with “umbrella headers” you can include:

- `Engine Modules/ECS.hpp`
- `Engine Modules/World.hpp`
- `Engine Modules/Graphics.hpp`
- `Engine Modules/Input.hpp`
- `Engine Modules/GameState.hpp`
- `Engine Modules/Audio.hpp`

The example engine lifecycle lives in:

- `Engine Modules/User/ACECS.hpp`
- `Engine Modules/User/ACECS.cpp`

---

## Core concepts

### ECS

**Entities**
- Entities are stored and managed by `EntityManager`.
- Entity IDs are `uint32_t` (`EntityId`).
- Global capacity settings exist as externs:
  - `MAX_ENTITIES`
  - `MAX_COMPONENT_TYPES`
  - `MAX_EVENT_TYPES`
  (defined in `Engine Modules/User/ECSRegistry.cpp`)

Key API (see `Engine Modules/ECS/Entities/EntityManager.hpp`):
- `EntityId entityCreate(...)`
- `Entity& entityCreateAndGet(...)`
- `Entity& entityGet(EntityId)`
- `void entitiesIntangibleUpdate()`
- `void entitiesQueuedUpdate()`

**Update types**
Defined in `Engine Modules/ECS/TypeDefinitions.hpp`:

- `EntityUpdateType::Frame` — updated every frame (via level updates or intangible updates)
- `EntityUpdateType::Never` — not updated by the updater (still updated once when created / can be updated manually)
- `EntityUpdateType::Observation` — updated only when observed (project-specific behavior via level logic)

**Components**
- Components are stored per-entity in a `std::vector<ComponentUniquePtr>` indexed by type ID.
- Component IDs are assigned through a type registry system (`TypeIDAllocator`) and initialized in `User/ECSRegistry.cpp`.
- Entities provide helper methods:
  - `entityComponentHas<T>()`
  - `entityComponentGet<T>()`
  - `entityComponentAdd<T>(...)`
  - plus index-based variants

**Component templates**
ACECS supports named “component templates” so you can spawn entities with a predefined component set.

Example initialization (see `Engine Modules/User/ECSRegistry.cpp`):
- `ComponentTemplateManager::componentTemplateAdd("Example Template", {...})`

Spawn example:
- `EntityManager::entityCreate("Example Template", EntityUpdateType::Frame);`

---

### Events

Events are stored per-entity by event type ID:

- `Entity::eventsVector` is a `std::vector<EventVector>`
- `EventVector` is `std::vector<EventUniquePtr>`

Important behavior:
- Event type IDs are assigned during registry initialization (ordering matters for update behavior).
- Events are allocated via `EventPool` to reduce allocations.

Entity event helpers (see `Engine Modules/ECS/Entities/Entity.hpp`):
- `entityEventAdd<T>()`
- `entityEventAddAndGet<T>()`
- `entityEventHas<T>()`
- `entityEventGet<T>(index)` / `entityEventGetSafe<T>(index)`
- `entityEventTerminate<T>(index)`
- `entityEventTerminateAllOfType<T>()`
- `entityEventGetAllOfType<T>()` returns a typed view (`CastedVector`)

---

### World / Levels

ACECS includes a lightweight “level grid” world model:

- `BaseLevel` represents a container for entity IDs grouped by update type.
- `LevelGrid<T>` manages a **3D grid** of levels (it can behave like 1D/2D by using depth/height of 1).
- `levelsActiveVector` tracks active/updating levels.

Key types and files:
- `Engine Modules/World/Level.hpp` — `BaseLevel` and entity ID lists
- `Engine Modules/User/GameLevel.hpp` — example `GameLevel : BaseLevel` (adds `exampleVariable`)
- `Engine Modules/World/LevelGrid.hpp` — `LevelGrid` and global `levelGrid`
- `Engine Modules/World/LevelUpdater.hpp` — `LevelUpdater::levelsUpdate()`

Typical flow:
- Initialize the grid: `GameLevelGrid::levelGridInitialize(width, height, depth);`
- Add a level: `GameLevelGrid::levelAdd(new GameLevel(...), startActive);`
- Update active levels each tick: `LevelUpdater::levelsUpdate();`

Observed entities:
- `BaseLevel` includes `entitiesObserved` and a virtual `entitiesObservedUpdate()` hook (project-defined).

---

### Panels (Rendering)

Rendering is built around **Panels**—independent viewports rendered to their own textures and composited to the main window.

Key files:
- `Engine Modules/Graphics/Panel.hpp`
- `Engine Modules/Graphics/PanelManager.hpp`
- `Engine Modules/Graphics/WindowHolder.hpp`

`Panel` highlights:
- Owns an `sf::RenderTexture` and `sf::View`
- Has:
  - `screenRect` (where the panel appears in the window)
  - `viewRect` (world-space view framing)
- Utilities:
  - zoom (`viewZoomScale`, `viewZoomSet`, `viewZoomGet`)
  - movement (`viewMove`)
  - rotation (`viewSetRotation`, `viewRotate`)
  - mouse helpers (`panelMousePositionGet`, `viewMousePositionGet`)
- Rendering calls:
  - `panelDrawObjects()` (calls the panel’s internal `panelUpdate()` to draw)
  - `panelRender(window)`
  - `panelClear()`

Panel storage:
- `PanelManager::panelAdd(name, PanelPtr)`
- `PanelManager::panelGet(name)`

Example panel type:
- `Engine Modules/User/Panels.hpp` defines `PanelGameView : Panel`

---

### Input

ACECS provides a named input mapping layer:

Key files:
- `Engine Modules/Input/InputInterface.hpp`
- `Engine Modules/Input/Key Events/KeyRecorder.*`
- `Engine Modules/Input/Key Events/KeyEventDefinitions.hpp`
- `Engine Modules/Input/Input Events/InputEventDefinitions.hpp`

Key ideas:
- Inputs are registered by a string name (`InputName` is `const char*`)
- Each input is bound to a **KeySet** (a set of `KeyEvent`s)
- Key logic:
  - `Or` (default): any key active → input active
  - `And`: all keys must be active → input active
- Key transitions:
  - `Pressed`, `Held`, `Released`

Example registrations (see `Engine Modules/User/ACECS.cpp`):
- `"Pause"` → `Escape Pressed`
- `"Move Right"` → `D Held` OR `Right Held` (etc.)

Runtime usage:
- `InputInterface::inputUpdate();`
- `InputInterface::eventsProcess(window);`
- `InputInterface::inputGetActive("Pause");`

Key name mapping:
- `KeyRecorder` maps names like `"W"`, `"Escape"`, `"Right"`, etc. to `sf::Keyboard::Key`
  (see `Engine Modules/Input/Key Events/KeyRecorder.cpp`).

---

### Game States

Game states are used to control what updates and what renders (e.g. play vs pause).

Key files:
- `Engine Modules/GameState/GameStateHandler.hpp`
- `Engine Modules/User/GameStates.hpp`
- `Engine Modules/User/GameStates.cpp`

State transitions:
- Each state has a list of `GameStateTransition` entries.
- A transition has:
  - destination state
  - a list of input names that trigger it

Example included:
- `GameStatePlay` updates:
  - `EntityManager::entitiesIntangibleUpdate()`
  - `EntityManager::entitiesQueuedUpdate()`
  - `LevelUpdater::levelsUpdate()`
- `GameStatePause` does nothing (pauses world/ECS updates in the example).

---

### Saving / Loading

Saving is structured as:

- `SaveHandler` — file stream handling + helpers
- `SaveDirector` — controls save/load sequence and delegates “game data” serialization

Key files:
- `Engine Modules/Saving/SaveHandler.hpp`
- `Engine Modules/Saving/SaveDirector.hpp`
- `Engine Modules/User/SaveOperations.hpp/.cpp`
- `Engine Modules/User/SaveFunctions.cpp`

Engine entry points:
- `Engine::engineSave()`
- `Engine::engineLoad()` (only loads if a save file exists)

Binary IO helpers:
- `SaveOperations` provides `<<` / `>>` for primitives, vectors, strings, and an example `GameLevel` implementation.

**Note:** `User/SaveFunctions.cpp` contains commented-out `SaveDirector::gameDataSave()` / `gameDataLoad()` stubs (intended to be defined in the actual game project).

---

## Using ACECS in your own app

### Include paths

Add these include directories to your project:

- `ACECS-Engine/Engine Modules/`
- `ACECS-Engine/SFMLInclude/`

ACECS uses relative includes internally (for example `#include "../Graphics.hpp"` inside `User/ACECS.hpp`), so keeping `Engine Modules/` as an include root is important.

### Linking SFML

This repo includes SFML 3.0.0 headers and libraries:

- Headers: `SFMLInclude/`
- Libs: `SFMLLib/`

Link the SFML libraries your app uses (commonly):
- `sfml-system`
- `sfml-window`
- `sfml-graphics`
- `sfml-audio`

Static variants are provided (`*-s.lib` and `*-s-d.lib`). If you use static libraries, define:
- `SFML_STATIC`

Depending on your configuration, you may also need to link SFML dependencies included in `SFMLLib/` (e.g. freetype, ogg/vorbis, flac, etc.) along with standard Windows libs.

If you link non-static SFML libs (without `-s`), you’ll need the matching SFML DLLs available at runtime.

---

## Minimal `main()` example

ACECS provides the engine lifecycle in `Engine Modules/User/ACECS.*`. A minimal host application looks like this:

```cpp
#include "User/ACECS.hpp"
#include "Graphics/WindowHolder.hpp"

int main() {
    WindowHolder::windowInitialize({1280.f, 720.f}, "ACECS Demo");
    auto& window = WindowHolder::windowGet();

    Engine::engineInitialize();

    while (window.isOpen()) {
        Engine::engineInputUpdate(window);
        Engine::engineUpdate();

        window.clear();
        Engine::engineDraw(window);
        window.display();
    }

    Engine::engineTerminate();
    return 0;
}
```

What it does:
- `engineInitialize()` initializes RNG, creates a 1×1×1 level grid + a `GameLevel`, registers inputs, panels, ECS IDs/templates/events, and sets the initial game state.
- `engineInputUpdate(window)` runs input update + processes SFML window events.
- `engineUpdate()` runs the `GameStateHandler` (which runs `Play` or `Pause` logic).
- `engineDraw(window)` draws the panels owned by the active game state.

---

## Example “User” layer

The `Engine Modules/User/` folder shows the intended “game-side wiring”:

- `ACECS.cpp/.hpp`
  - `inputsRegister()`
  - `panelsRegister()`
  - `gameStatesRegister()`
  - `imagesRegister()` / `texturesRegister()` / `audioRegister()` stubs
  - lifecycle: `engineInitialize`, `engineInputUpdate`, `engineUpdate`, `engineDraw`, `engineTerminate`, `engineSave`, `engineLoad`
- `ECSRegistry.cpp/.hpp`
  - ECS initialization/termination
  - component/event ID registration
  - component template registration
  - example component system function (`ComponentExample::system`)
- `GameStates.cpp/.hpp`
  - example `Play` and `Pause` game states
- `Panels.cpp/.hpp`
  - example `PanelGameView` type (panel hook)
- `GameLevel.cpp/.hpp`
  - example `GameLevel` derived from `BaseLevel`
- `SaveOperations.cpp/.hpp`
  - binary save operators and examples
- `SaveFunctions.cpp`
  - commented stubs for game-specific save/load sequencing

---

## Notes

- There is **no standalone executable** and **no `main()`** in this repo by design.
- The engine is modular; you can use only the pieces you want, but the example lifecycle in `User/ACECS.*` demonstrates a complete wiring path.
- SFML is bundled here (headers + libs) to make the framework self-contained.
