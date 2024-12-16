import serial
import pygame

dataArray = []
bridgeActive = False
serialPort = 'COM18'
baudRate = 115200

surface = pygame.Surface((8, 8))

def map_range(x, in_min, in_max, out_min, out_max):
  return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

def value_to_color(value):
    normalized = map_range(value, 0, 1000, 0, 255)    
    red = int((255 - normalized))
    green = int(normalized)
    return (red, green, 0)  # RGB color (no blue component)

def draw_grid():
    global dataArray
    for row in range(GRID_SIZE):
        for col in range(GRID_SIZE):
            # Get the value from the data array
            value = int(dataArray[row][col])
            # Trim the value to a maximum of 2500
            value = min(value, 1000)
            # Get the corresponding color
            color = value_to_color(value)
            # Draw the cell
            # pygame.draw.rect(screen, color, pygame.Rect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE))
            surface.set_at((col, row), color)
            pygame.transform.smoothscale(surface, (400, 400), screen)

if __name__ == '__main__':

    pygame.init()

    WINDOW_SIZE = 400  # Window size (width and height)
    GRID_SIZE = 8  # 8x8 grid
    CELL_SIZE = WINDOW_SIZE // GRID_SIZE  # Size of each cell (50x50)

    # Create the Pygame window
    screen = pygame.display.set_mode((WINDOW_SIZE, WINDOW_SIZE))
    pygame.display.set_caption("8x8 Pixel Grid")

    ok = True

    try:
        serialPort = serial.Serial(serialPort, baudRate)
    except serial.SerialException:
        ok = False

    if ok:
        serialPort.timeout = 0.4
        while True:
            line = list(map(int, serialPort.readline().decode(errors='replace').split("\t")[1:])) 
            if len(line) == 8:
                dataArray.append(line)
                try:
                    dataArray[-1][-1] = dataArray[-1][-1].rstrip('\r\n')
                except:
                    pass
                if len(dataArray) == 8:
                    # for row in dataArray:
                    #     print(row)
                    # print()
                    # print()

                    # Fill the screen with white
                    screen.fill((255, 255, 255))

                    # Draw the grid
                    draw_grid()

                    # Update the screen
                    pygame.display.flip()

                    dataArray = []



        
        
        

            



