import pygame
import sys
import random
import os

# Initialize Pygame
pygame.init()

# Screen dimensions
screen_width = 800
screen_height = 600

# Set up the game window
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("2D Climbing Platformer")

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)


# Define player attributes
player_size = 50
player_color = BLUE
player_x = 100
player_y = 500
player_speed = 5
player_velocity_y = 0
player_on_ground = False

# Define gravity
gravity = 0.1

# Define platform attributes
platform_width = 100
platform_height = 20
platforms = [pygame.Rect(random.randint(0, screen_width - platform_width), random.randint(0, screen_height - platform_height), platform_width, platform_height) for _ in range(10)]

# Set player initial position on a platform
initial_platform = random.choice(platforms)
player_x = initial_platform.x + (platform_width - player_size) // 2
player_y = initial_platform.y - player_size

#hazard attributes
hazard_size = 30
hazards = [pygame.Rect(random.randint(0, screen_width - hazard_size), random.randint(0, screen_height - hazard_size), hazard_size, hazard_size) for _ in range(5)]

# Star Attributes
star_size = 20
stars = [pygame.Rect(random.randint(0, screen_width - star_size), random.randint(0, screen_height - star_size), star_size, star_size) for _ in range(5)]


# Define scrolling
scroll_y = 0
scroll_speed = 10
scroll_threshold = screen_height * 0.25

# Define score
score = 0
highest_y = player_y

# Read high score from file
high_score_file = "high_score.txt"
if os.path.exists(high_score_file):
    with open(high_score_file, "r") as f:
        high_score = int(f.read())
else:
    high_score = 0

font = pygame.font.SysFont(None, 36)

# Main game loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Get the current state of all keyboard buttons
    keys = pygame.key.get_pressed()

    # Update player position based on key presses
    if keys[pygame.K_LEFT]:
        player_x -= player_speed
    if keys[pygame.K_RIGHT]:
        player_x += player_speed
    if keys[pygame.K_SPACE] and player_on_ground:
        player_velocity_y = -10  # Jumping
        player_on_ground = False

    # Apply gravity
    player_velocity_y += gravity
    player_y += player_velocity_y

    # Check for collisions with platforms
    player_rect = pygame.Rect(player_x, player_y, player_size, player_size)
    player_on_ground = False
    for platform in platforms:
        if player_rect.colliderect(platform) and player_velocity_y > 0:
            player_y = platform.y - player_size
            player_velocity_y = 0
            player_on_ground = True

    # Check for collisions with hazards
    for hazard in hazards:
        if player_rect.colliderect(hazard):
            running = False

    # Check for collisions with stars
    for star in stars:
        if player_rect.colliderect(star):
            score += 10
            stars.remove(star)
            stars.append(pygame.Rect(random.randint(0, screen_width - star_size), random.randint(-screen_height // 2, -star_size), star_size, star_size))


    # update score based on height climbed
    if player_y < highest_y:
        highest_y = player_y
        score += 1

     # Update high score
    if score > high_score:
        high_score = score


    # Scroll the screen up when the player reaches the top
    if player_y < scroll_threshold:
        scroll_y = scroll_speed
        player_y += scroll_y
        for platform in platforms:
            platform.y += scroll_y
        for hazard in hazards:
            hazard.y += scroll_y
        for star in stars:
            star.y += scroll_y
    else:
        scroll_y = 0

    # IF player goes below the screen then game over
    if player_y > screen_height:
        running = False

    # Player spawns on a platform
    if player_x < 0:
        player_x = screen_width - player_size
    if player_x > screen_width - player_size:
        player_x = 0

    # Generate new platforms as old ones disapear
    for platform in platforms:
        if platform.y > screen_height:
            platform.x = random.randint(0, screen_width - platform_width)
            platform.y = random.randint(-screen_height // 2, -platform_height)

    # Hazards generation
    for hazard in hazards:
        if hazard.y > screen_height:
            hazard.x = random.randint(0, screen_width - hazard_size)
            hazard.y = random.randint(-screen_height // 2, -hazard_size)

    # Stars generation
    for star in stars:
        if star.y > screen_height:
            star.x = random.randint(0, screen_width - star_size)
            star.y = random.randint(-screen_height // 2, -star_size)

    # Abilities perhaps //stretch

    # Clear the screen
    screen.fill(WHITE)

    # Draw the platforms
    for platform in platforms:
        pygame.draw.rect(screen, BLACK, platform)

    # Draw the hazards
    for hazard in hazards:
        pygame.draw.rect(screen, RED, hazard)

    # Draw the stars
    for star in stars:
        pygame.draw.rect(screen, YELLOW, star)

    # Draw the score
    score_text = font.render(f"Score: {score}", True, BLACK)
    screen.blit(score_text, (10, 10))

    # Draw the high score
    high_score_text = font.render(f"High Score: {high_score}", True, BLACK)
    screen.blit(high_score_text, (10, 50))

    # Draw the player
    pygame.draw.rect(screen, player_color, (player_x, player_y, player_size, player_size))

    # Update the display
    pygame.display.flip()

    # Cap the frame rate
    pygame.time.Clock().tick(60)

# Write high score to file
with open(high_score_file, "w") as file:
    file.write(str(high_score))

# Quit Pygame and exit the program
pygame.quit()
sys.exit()
