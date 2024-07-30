from matplotlib import pyplot as plt
import os

def show_test_result(name: str) -> None:
    arrows = []
    trajectories = [] # List of tuples (tag, [(x, y)])
    with open(f"store/{name}.txt") as file:
        for line in file:
            parts = line[line.find("(")+1:line.find(")")].split(",")
            if line.startswith("Arrow"):
                arrows.append((float(parts[0]), float(parts[1]), float(parts[2]), float(parts[3])))
            elif line.startswith("Point"):
                # Get tag in [...]
                tag = line[line.find("[")+1:line.find("]")]
                found = False
                for tag_, trajectory in trajectories:
                    if tag == tag_:
                        trajectory.append((float(parts[0]), float(parts[1])))
                        found = True
                if not found:
                    trajectories.append((tag, [(float(parts[0]), float(parts[1]))]))
    print(len(trajectories))
    arrows = arrows[::73]
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
    LIM = 10
    # Rmove all points outside of the range -LIM to LIM
    trajectories = [(tag, [(x, y) for x, y in trajectory if -LIM < x < LIM and -LIM < y < LIM]) for tag, trajectory in trajectories]
    for tag, trajectory in trajectories:
        x = [point[0] for point in trajectory]
        y = [point[1] for point in trajectory]
        ax.plot(x, y, label=tag, linewidth=0.5)  # Draw thin lines between points
        ax.scatter(x, y)  # Plot the points as well
    pos = ax.get_position()
    ax.set_position([pos.x0, pos.y0, pos.width * 0.9, pos.height])
    ax.legend(loc='center right', bbox_to_anchor=(1.25, 0.5))
    plt.xlim(-LIM, LIM)
    plt.ylim(-LIM, LIM)
    plt.savefig(f"store/{name}.png")
    plt.clf()
    plt.close(fig)

if __name__ == "__main__":
    # Loop throuh all .txt files in store folder
    for file in os.listdir("store"):
        if file.endswith(".txt"):
            name = file[:-4]
            show_test_result(name)