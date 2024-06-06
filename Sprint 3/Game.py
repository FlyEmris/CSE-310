import pygame
import sys
import random

pygame.init()


screen_width = 800
screen_height = 600

screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("My First Game")

player_size = 50
player_color = (0, 255, 0)
player_x = 375
player_y = 275
player_speed = 1

enemy_size = 50
enemy_color = (255, 0, 0)
enemy_x = random.randint(0, 750)
enemy_y = random.randint(0, 550)
enemy_speed = 1

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()

    if keys[pygame.K_LEFT]:
        player_x -= player_speed
    if keys[pygame.K_RIGHT]:
        player_x += player_speed
    if keys[pygame.K_UP]:
        player_y -= player_speed
    if keys[pygame.K_DOWN]:
        player_y += player_speed

    screen.fill((0, 0, 0))

    pygame.draw.rect(screen, player_color, (player_x, player_y, player_size, player_size))
            

    pygame.draw.rect(screen, enemy_color, (enemy_x, enemy_y, enemy_size, enemy_size))

    pygame.display.flip()

pygame.quit()
sys.exit()