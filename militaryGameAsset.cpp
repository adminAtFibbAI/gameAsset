#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp> // For vector math

// Forward declarations
class Weapon;
class Animation;
class PhysicsComponent;

class MilitaryCharacter {
public:
    struct CharacterStats {
        float health = 100.0f;
        float stamina = 100.0f;
        float speed = 5.0f;
        float rotationSpeed = 180.0f; // degrees per second
        float crouchSpeedMultiplier = 0.5f;
        float sprintSpeedMultiplier = 1.5f;
    };

    struct AnimationState {
        bool isRunning = false;
        bool isCrouching = false;
        bool isAiming = false;
        bool isShooting = false;
        bool isReloading = false;
    };

private:
    // Core components
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 velocity;
    CharacterStats stats;
    AnimationState animState;
    std::shared_ptr<PhysicsComponent> physics;
    
    // Inventory and equipment
    std::shared_ptr<Weapon> currentWeapon;
    std::vector<std::shared_ptr<Weapon>> inventory;
    
    // Animation system
    std::unique_ptr<Animation> currentAnimation;
    std::map<std::string, std::unique_ptr<Animation>> animations;

public:
    MilitaryCharacter(const glm::vec3& startPos = glm::vec3(0.0f))
        : position(startPos), rotation(0.0f), velocity(0.0f) {
        InitializePhysics();
        LoadAnimations();
    }

    // Movement methods
    void Move(const glm::vec3& direction, float deltaTime) {
        glm::vec3 moveDirection = glm::normalize(direction);
        
        float currentSpeed = stats.speed;
        if (animState.isCrouching) {
            currentSpeed *= stats.crouchSpeedMultiplier;
        } else if (animState.isRunning) {
            currentSpeed *= stats.sprintSpeedMultiplier;
        }

        velocity = moveDirection * currentSpeed;
        position += velocity * deltaTime;
        
        UpdateAnimation();
        physics->UpdateCollision(position);
    }

    void Rotate(float yawDelta, float deltaTime) {
        rotation.y += yawDelta * stats.rotationSpeed * deltaTime;
        // Normalize rotation to 0-360 degrees
        rotation.y = fmod(rotation.y, 360.0f);
    }

    // Combat methods
    bool PickupWeapon(std::shared_ptr<Weapon> weapon) {
        if (inventory.size() < MAX_WEAPONS) {
            inventory.push_back(weapon);
            if (!currentWeapon) {
                currentWeapon = weapon;
            }
            return true;
        }
        return false;
    }

    void Shoot() {
        if (currentWeapon && !animState.isReloading) {
            if (currentWeapon->CanShoot()) {
                animState.isShooting = true;
                currentWeapon->Shoot();
                PlayAnimation("shoot");
            } else if (currentWeapon->NeedsReload()) {
                Reload();
            }
        }
    }

    void Reload() {
        if (currentWeapon && !animState.isReloading) {
            animState.isReloading = true;
            currentWeapon->StartReload();
            PlayAnimation("reload");
        }
    }

    // State changes
    void ToggleCrouch() {
        animState.isCrouching = !animState.isCrouching;
        UpdateAnimation();
    }

    void StartSprint() {
        if (!animState.isCrouching && !animState.isAiming) {
            animState.isRunning = true;
            UpdateAnimation();
        }
    }

    void StopSprint() {
        animState.isRunning = false;
        UpdateAnimation();
    }

    // Animation handling
    void UpdateAnimation() {
        std::string animName = DetermineAnimation();
        PlayAnimation(animName);
    }

private:
    void InitializePhysics() {
        physics = std::make_shared<PhysicsComponent>();
        // Set up collision capsule and physics properties
        physics->SetCollisionCapsule(0.5f, 2.0f); // radius, height
        physics->SetMass(80.0f); // kg
    }

    void LoadAnimations() {
        // Load animation data for different states
        animations["idle"] = std::make_unique<Animation>("idle.anim");
        animations["walk"] = std::make_unique<Animation>("walk.anim");
        animations["run"] = std::make_unique<Animation>("run.anim");
        animations["crouch"] = std::make_unique<Animation>("crouch.anim");
        animations["shoot"] = std::make_unique<Animation>("shoot.anim");
        animations["reload"] = std::make_unique<Animation>("reload.anim");
    }

    std::string DetermineAnimation() {
        if (animState.isReloading) return "reload";
        if (animState.isShooting) return "shoot";
        if (animState.isCrouching) return "crouch";
        if (animState.isRunning) return "run";
        if (glm::length(velocity) > 0.1f) return "walk";
        return "idle";
    }

    void PlayAnimation(const std::string& animName) {
        if (animations.find(animName) != animations.end()) {
            currentAnimation = std::make_unique<Animation>(*animations[animName]);
            currentAnimation->Play();
        }
    }

    static const size_t MAX_WEAPONS = 3;
};

// Weapon system
class Weapon {
public:
    struct WeaponStats {
        int maxAmmo;
        int currentAmmo;
        float damage;
        float range;
        float reloadTime;
        float fireRate;
    };

private:
    WeaponStats stats;
    std::string weaponType;
    float lastShotTime;
    bool isReloading;

public:
    Weapon(const std::string& type, const WeaponStats& initialStats)
        : weaponType(type), stats(initialStats), lastShotTime(0.0f), isReloading(false) {}

    bool CanShoot() const {
        return !isReloading && stats.currentAmmo > 0;
    }

    bool NeedsReload() const {
        return stats.currentAmmo == 0;
    }

    void Shoot() {
        if (CanShoot()) {
            stats.currentAmmo--;
            lastShotTime = GetCurrentTime();
            // Implement shooting logic (raycasting, projectile spawning, etc.)
        }
    }

    void StartReload() {
        if (!isReloading) {
            isReloading = true;
            // Start reload timer
        }
    }

private:
    float GetCurrentTime() {
        // Implementation to get current game time
        return 0.0f;
    }
};
