# 🧛🌕🐺 OOP Grid-Based Strategy Game in C++

This project is a turn-based strategy game implemented in C++ using object-oriented programming. Players control an Avatar navigating a grid filled with NPCs, werewolves, vampires, trees, water, and magic potions. The world evolves turn by turn based on a day-night cycle, with each entity type exhibiting unique movement and interaction logic.

## Features

- **Entity System**: Includes classes for Avatar, NPCs, Werewolves, Vampires, Board, and Block.
- **Game Board**: Dynamically generated grid-based environment (min size 4x4, max 100x100).
- **AI Behavior**: Entities move and interact using decision-making logic (e.g., attack, heal, avoid).
- **Day-Night Cycle**: Alternates every 8 avatar moves; entity behavior changes accordingly.
- **Entity Interactions**:
  - Vampires move diagonally but only interact with adjacent orthogonal entities.
  - Entities can heal, attack, or die (starting life: 3).
  - Entities with strength ≥ 3 can attack.
- **Obstacle Handling**: Trees (`*`) and water (`~`) can block player or NPC movement.
- **Game Visualization**: Display includes symbols for all elements (e.g., `w` for werewolves, `+` for potions).
- **Auto-Restart**: Game resets if the avatar gets completely stuck.

## File Structure

- `project_main.cpp`: Initializes the game and handles memory.
- `game_input.cpp`: Manages user input and avatar-related logic.
- `Decide.cpp`: Contains AI logic for NPC movement and decisions.
- `Entity.cpp`: Implements core entity classes and behaviors.
- `Board.cpp`: Manages board state, entity spawning, and tile interactions.
- `game.h`: Declares all major classes and shared interfaces.
- `game_input.h`: Declares utility functions related to game input.

## How to Run

Built with:
- **OS**: Windows
- **IDE**: Visual Studio
- **Language**: C++

Clone the repo:
```bash
git clone https://github.com/DimitrisChrysos/project_oop.git
```

## Gameplay Preview

Watch a demonstration on YouTube:  
🔗 [Gameplay Video](https://www.youtube.com/watch?v=cCJWJ2bw10s)

## Contributors

- **Δημήτριος Χρυσός** (sdi2100275@di.uoa.gr)  
- **Αναστάσιος Μουμουλίδης** (sdi2100108@di.uoa.gr)

---

This project was developed as part of the **Object-Oriented Programming** course to practice class design, grid logic, and basic game architecture in C++.
