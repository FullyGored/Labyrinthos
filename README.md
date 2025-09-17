# Project: Labyrinthos

[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.4-blueviolet)](https://www.unrealengine.com/en-US)
[![Status](https://img.shields.io/badge/Status-In%20Development-orange)](https://github.com/FullyGored/PixelWarriors-Framework)
[![License](https://img.shields.io/badge/License-MIT-blue)](LICENSE)

A vertical slice project to develop a procedural maze game in Unreal Engine 5. This repository serves as the foundational proving ground for the **"PW Framework,"** a modular, C++ first architecture designed for high-performance, scalable game systems.

<!-- A great place for a gameplay GIF or a hero screenshot! -->
![Gameplay Screenshot](/_readme_assets/promo_image.png)

## Overview

Labyrinthos is the first major development milestone in a 12-month professional training roadmap. While a self-contained game slice, its primary purpose is to prototype and perfect core systems that will be deployed in the flagship project, **"PixelWarriors,"** a team-based tactical FPS.

This project is being built from the ground up with a focus on clean, efficient, and well-documented C++ code, leveraging Unreal Engine's architecture for a data-driven design.

## Core Architectural Pillars

The project adheres strictly to the "PW Framework" doctrine:

*   **C++ First:** Core gameplay systems, player logic, and data structures are built in C++ for maximum performance and stability.
*   **Blueprints for Data & Expression:** Blueprints inherit from C++ base classes. They are used exclusively to assign assets (meshes, materials, sounds), tune values, and implement simple, non-performant, event-driven logic.
*   **Data-Driven Design:** The maze itself is defined by data. The V1 implementation uses a C++ `UDataAsset` to define maze layouts, while the V2 implementation (in progress) will use a library of hand-crafted **Level Instance** modules.
*   **Modular & Event-Driven UI:** The UI will be built using a Lyra-inspired, C++ managed system built on the `CommonUI` plugin. HUD elements are updated via C++ Delegates, **never** on `Event Tick`.

## Current Features (C++ Foundation)

*   **Core C++ Gameplay Framework:**
    *   `ALabyrinthosCharacter`
    *   `ALabyrinthosPlayerController`
    *   `ALabyrinthosGameMode`
*   **C++ Data Asset (`ULabyrinthosMazeData`):** A custom Data Asset to hold maze layout information for the V1 generator.
*   **V1 Maze Generator (`ALabyrinthosMazeGenerator`):** A C++ Actor that can read `ULabyrinthosMazeData` and spawn a maze from Instanced Static Meshes.

## The Roadmap: V2 - Modular PCG

The project is currently pivoting to a far more powerful and performant V2 procedural generation system.

1.  **Fabricate Module Library:** Hand-craft a library of 5x5 maze "modules" (4-ways, corners, dead-ends, etc.) as **Level Instance** assets.
2.  **Develop PCG Graph:** Create a master PCG (Procedural Content Generation) graph that intelligently selects, rotates, and assembles these modules to build the final maze.
3.  **Implement HiGen (Hierarchical Generation):** The PCG graph will use partitioning to only spawn and load maze chunks immediately around the player, allowing for massive, world-sized mazes with near-zero performance cost.
4.  **Lyra UI Implementation:** Build out the full UI suite, including a main menu, HUD, and a data-persistent leaderboard.
5.  **Art & Audio Polish Pass:** Integrate final "Gemi" character assets, our established color theory, and a full audio soundscape.

## Setup & Build

1.  Clone this repository.
2.  Right-click the `.uproject` file and select "Generate Visual Studio project files".
3.  Open the `.sln` file in Visual Studio and build the solution.
4.  Press F5 or open the project in the Unreal Editor and press Play.

---

This project is licensed under the MIT License. See `LICENSE` for more information.
