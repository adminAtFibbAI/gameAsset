# gameAsset
gameAssetPOC for Abdrew
# Military Character System
A comprehensive C++ character system designed for military-style games, featuring weapon handling, movement mechanics, and animation states created using fibb.ai

## 🎮 Features

### Character Movement
- **Basic Movement**: Full 3D movement with position and rotation control
- **Movement States**:
  - Walking
  - Running/Sprinting
  - Crouching
  - Aim walking
- **Physics Integration**:
  - Collision detection
  - Realistic movement constraints
  - Physics-based character controller

### Combat System
- **Weapon Management**:
  - Multiple weapon support (up to 3 weapons)
  - Weapon pickup system
  - Dynamic weapon switching
  - Ammo management
- **Combat Actions**:
  - Shooting mechanics
  - Reloading system
  - Aim down sights
  - Different fire modes (configurable per weapon)

### Animation System
- **State-Based Animations**:
  - Idle animations
  - Movement animations (walk, run, crouch)
  - Combat animations (shoot, reload)
  - Smooth transitions between states
- **Blend Support**:
  - Upper body combat animations
  - Lower body movement animations
  - Transition blending

## 🛠️ Technical Requirements

### Dependencies
- GLM (OpenGL Mathematics)
- C++17 or higher
- Memory management through smart pointers

### Integration Requirements
```cpp
// Required headers
#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>
```

## 🚀 Quick Start

### 1. Basic Character Setup
```cpp
// Create a character at position (0,0,0)
MilitaryCharacter soldier;

// Create a character at specific position
glm::vec3 startPos(10.0f, 0.0f, 10.0f);
MilitaryCharacter soldier(startPos);
```

### 2. Movement Control
```cpp
// Move character
glm::vec3 direction(1.0f, 0.0f, 0.0f); // Move right
float deltaTime = 0.016f; // 60 FPS
soldier.Move(direction, deltaTime);

// Rotate character
float yawDelta = 90.0f; // Rotate 90 degrees
soldier.Rotate(yawDelta, deltaTime);
```

### 3. Weapon Handling
```cpp
// Create and pick up a weapon
auto rifle = std::make_shared<Weapon>("Rifle", WeaponStats{...});
soldier.PickupWeapon(rifle);

// Combat actions
soldier.Shoot();
soldier.Reload();
```

## 🔧 Customization

### Character Stats
You can customize various character attributes through the `CharacterStats` struct:
```cpp
CharacterStats stats;
stats.health = 150.0f;            // More health
stats.speed = 6.0f;               // Faster movement
stats.sprintSpeedMultiplier = 2.0f; // Faster sprinting
```

### Weapon Configuration
Customize weapons through the `WeaponStats` struct:
```cpp
WeaponStats rifleStats;
rifleStats.maxAmmo = 30;
rifleStats.damage = 35.0f;
rifleStats.range = 100.0f;
rifleStats.reloadTime = 2.0f;
rifleStats.fireRate = 600.0f; // Rounds per minute
```

## 🎯 Example Usage

### Complete Movement System
```cpp
// Game loop example
void UpdateCharacter(MilitaryCharacter& character, float deltaTime) {
    // Get input (implement your input system)
    glm::vec3 moveInput = GetMovementInput();
    float rotateInput = GetRotationInput();

    // Update character
    character.Move(moveInput, deltaTime);
    character.Rotate(rotateInput, deltaTime);

    // Handle actions
    if (IsSprintKeyPressed()) {
        character.StartSprint();
    }
    if (IsCrouchKeyPressed()) {
        character.ToggleCrouch();
    }
    if (IsShootKeyPressed()) {
        character.Shoot();
    }
    if (IsReloadKeyPressed()) {
        character.Reload();
    }
}
```

## 🔍 Implementation Details

### Physics System
The character uses a capsule collider for physics interactions:
- Radius: 0.5 units
- Height: 2.0 units
- Mass: 80.0 kg

### Animation System
Animations are loaded from files and managed through state machines:
- Smooth transitions between states
- Support for animation blending
- Upper/lower body separation for combat animations

## ⚠️ Known Limitations

1. Maximum of 3 weapons in inventory
2. No prone position implementation
3. Basic animation system requires custom implementation
4. Physics system requires engine-specific implementation

## 🔜 Planned Features

1. Stance system (standing, crouching, prone)
2. Advanced weapon customization
3. Climbing system
4. Cover system
5. Team AI integration


## 📝 License

This project is available under the MIT License. Feel free to use and modify as needed for your game project.

## 📚 Additional Resources

- [GLM Documentation](https://github.com/g-truc/glm)
- [C++ Smart Pointers Guide](https://en.cppreference.com/w/cpp/memory/smart_ptr)
- [Game Physics Tutorials](https://gafferongames.com/)
