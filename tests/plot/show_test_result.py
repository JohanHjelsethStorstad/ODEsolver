from matplotlib import pyplot as plt
import os
import argparse
import json
import random

def show_test_result(name: str) -> None:
    config = json.load(open(f"tests/configs/{name}.json"))['test']
    arrows = []
    trajectories = {} # {tag: {start: [(x, y), ...]}}
    with open(f"tests/out/{name}.txt") as file:
        for line in file:
            parts = line[line.find("(")+1:line.find(")")].split(",")
            # Get tag in [...]
            tag = line[line.find("[")+1:line.find("]")]

            # Get start in {...}
            start = line[line.find("{")+1:line.find("}")]
            if line.startswith("Arrow"):
                arrows.append((float(parts[0]), float(parts[1]), float(parts[2]), float(parts[3])))
            elif line.startswith("Point"):
                if tag not in trajectories:
                    trajectories[tag] = {}
                if start not in trajectories[tag]:
                    trajectories[tag][start] = []
                trajectories[tag][start].append((float(parts[0]), float(parts[1])))
    
    #filter arrows:
    #Remve arrows outside window
    window = config['window']
    stratx = window['startx']
    endx = window['startx'] + window['width']
    straty = window['starty']
    endy = window['starty'] + window['height']
    for arrow in arrows:
        if arrow[0] < stratx or arrow[0] > endx or arrow[2] < stratx or arrow[2] > endx or arrow[1] < straty or arrow[1] > endy or arrow[3] < straty or arrow[3] > endy:
            arrows.remove(arrow)
    #choose some random arrows to actually render
    AMOUNT_OF_ARROWS_TO_RENDER = 700
    if len(arrows) > AMOUNT_OF_ARROWS_TO_RENDER:
        random.shuffle(arrows)
        arrows = arrows[:AMOUNT_OF_ARROWS_TO_RENDER]
    
    # Plot trajectory and arrows
    longest_length = 0
    for arrow in arrows:
        dx = arrow[2] - arrow[0]
        dy = arrow[3] - arrow[1]
        length = (dx**2 + dy**2)**0.5
        if length > longest_length:
            longest_length = length

    fig, ax = plt.subplots(figsize=(16, 10))
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
        
        ax.arrow(x, y, dx, dy, lw=1, head_width=0.1, head_length=0.1, color=color(length))
    for tag, starts in trajectories.items():
        xs = []
        ys = []
        #Choose a color
        color = f"#{hash(tag) & 0x00FFFFFF:06X}"
        for start, trajectory in starts.items():
            x, y = zip(*trajectory)
            ax.plot(x, y, color=color)  # Draw thin lines between points
            xs.append(x)
            ys.append(y)
        ax.scatter(xs, ys, label=tag, linewidth=0.5, color=color)  # Plot the points as well
    pos = ax.get_position()
    ax.set_position([pos.x0, pos.y0, pos.width * 0.9, pos.height])
    ax.legend(loc='center right', bbox_to_anchor=(1.25, 0.5))
    
    
    plt.xlim(stratx, endx)
    plt.ylim(straty, endy)

    plt.savefig(f"tests/out/{name}.png")
    plt.clf()
    plt.close(fig)

if __name__ == "__main__":
    # Loop throuh all .txt files in store folder
    # Look at argument for file name
    parser = argparse.ArgumentParser(description="Process some files.")
    parser.add_argument('filename', type=str, help='The name of the file to process')
    args = parser.parse_args()
    show_test_result(args.filename)