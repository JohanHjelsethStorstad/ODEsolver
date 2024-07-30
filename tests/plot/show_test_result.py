from matplotlib import pyplot as plt
import os

def show_test_result(name: str) -> None:
    arrows = []
    points_in_trajectory = []
    print(arrows)
    with open(f"store/{name}.txt") as file:
        for line in file:
            parts = line[line.find("(")+1:line.find(")")].split(",")
            if line.startswith("Arrow"):
                arrows.append((float(parts[0]), float(parts[1]), float(parts[2]), float(parts[3])))
            elif line.startswith("Point"):
                points_in_trajectory.append((float(parts[0]), float(parts[1])))
    arrows = arrows[::73]
    # Plot trajectory and arrows
    longest_length = 0
    for arrow in arrows:
        dx = arrow[2] - arrow[0]
        dy = arrow[3] - arrow[1]
        length = (dx**2 + dy**2)**0.5
        if length > longest_length:
            longest_length = length

    for arrow in arrows:
        x = arrow[0]
        y = arrow[1]
        dx = arrow[2] - arrow[0]
        dy = arrow[3] - arrow[1]
        length = (dx**2 + dy**2)**0.5
        dx = dx / length if length != 0 else dx
        dy = dy / length if length != 0 else dy
        #choose clor based on length. Red (#FF0000) is short, blue (#0000FF) is long
        amount_of_red = int(255 * (1 - length / longest_length))
        amount_of_blue = int(255 * (length / longest_length))
        color = lambda length: f"#{amount_of_red:02X}00{amount_of_blue:02X}"
        
        plt.arrow(x, y, dx, dy, lw=1, head_width=0.1, head_length=0.1, color=color(length))
    for point in points_in_trajectory:
        plt.plot(point[0], point[1], 'ro')
    plt.savefig(f"store/{name}.png")
    plt.clf()

if __name__ == "__main__":
    # Loop throuh all .txt files in store folder
    for file in os.listdir("store"):
        if file.endswith(".txt"):
            name = file[:-4]
            show_test_result(name)