import sys
import random


def generate_rooms(nb_rooms):
    rooms = []
    used_coords = set()

    for i in range(nb_rooms):
        name = str(i)

        while True:
            x = random.randint(0, 100)
            y = random.randint(0, 100)
            if (x, y) not in used_coords:
                used_coords.add((x, y))
                break

        rooms.append((name, x, y))

    return rooms


def generate_links(rooms, probability=0.1):
    links = set()
    room_names = [room[0] for room in rooms]

    for i in range(len(room_names)):
        for j in range(i + 1, len(room_names)):
            if random.random() < probability:
                link = f"{room_names[i]}-{room_names[j]}"
                links.add(link)

    return links


def write_file(filename, ants, rooms, links):
    with open("maps/" + filename + ".txt", "w") as f:
        f.write(f"{ants}\n")

        f.write("##start\n")
        start = rooms[0]
        f.write(f"{start[0]} {start[1]} {start[2]}\n")

        for room in rooms[1:-1]:
            f.write(f"{room[0]} {room[1]} {room[2]}\n")

        f.write("##end\n")
        end = rooms[-1]
        f.write(f"{end[0]} {end[1]} {end[2]}\n")

        for link in links:
            f.write(link + "\n")


def main():
    if len(sys.argv) != 4:
        print("Usage: python generator.py <filename> <ants> <rooms>")
        sys.exit(1)

    filename = sys.argv[1]
    ants = int(sys.argv[2])
    nb_rooms = int(sys.argv[3])

    if nb_rooms < 2:
        print("Il faut au moins 2 rooms")
        sys.exit(1)

    rooms = generate_rooms(nb_rooms)
    links = generate_links(rooms, 0.1)

    write_file(filename, ants, rooms, links)


if __name__ == "__main__":
    main()