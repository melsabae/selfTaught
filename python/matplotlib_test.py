#!/usr/bin/env python3


import matplotlib.gridspec
import matplotlib.pyplot
import PIL
import numpy
import itertools
import random


def main():
    data = list(map(lambda p: numpy.asarray(PIL.Image.open(p)), [
          "/usr/share/zenity/zenity-file.png"
        , "/usr/share/zenity/zenity-list.png"
        , "/usr/share/zenity/zenity-calendar.png"
        , "/usr/share/zenity/zenity-notification.png"
        , "/usr/share/zenity/zenity-scale.png"
        , "/usr/share/zenity/zenity-progress.png"
        , "/usr/share/zenity/zenity-entry.png"
    ]))

    # for n in [1, len(data)], generate a grid of 1 row with n columns
    gridspecs = list(map(lambda n: matplotlib.gridspec.GridSpec(1, n + 1), range(len(data))))

    # turn on interactive mode
    matplotlib.pyplot.ion()

    # generate a figure with 1 axis per image
    fig, axes = matplotlib.pyplot.subplots(1, len(data))

    # forever
    for i in itertools.count():
        # title is the iteration number
        fig.suptitle(str(i))

        # choose a random number of images to display
        k = random.randrange(1, 1 + len(data))

        # get a ref to the gridspec we need for k, k is 1-indexed
        gs = gridspecs[k - 1]

        # generate a set of k-sized subset of image indices to display
        v = set(random.sample(range(len(data)), k=k))

        # obtain the indices we will not display
        nv = set(range(len(data))) - v

        # turn of axes we don't want
        for n in nv:
            axes[n].set_visible(False)

        # for each axis we do want:
        #   clear it
        #   feed it an image
        #   re-flow its position
        #   give it a title
        #   make it visible
        for j, image_index in enumerate(v):
            axes[image_index].cla()
            axes[image_index].imshow(data[image_index])
            axes[image_index].set_position(gs[j].get_position(fig))
            axes[image_index].set_title(str(j))
            axes[image_index].set_visible(True)

        matplotlib.pyplot.pause(0.1)

    return 0


if __name__ == "__main__":
    exit(main())

