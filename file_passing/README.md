i remember doing this a few months ago, i forget the original motivation

the idea was to share files between processes, by passing file paths
the file paths would be shared memory, so that the sender/producer continues to keep the file around for other things
while the consumer gets a read-only view to do some sort of processing on it

i remember vaguely that the motivation was to avoid doing the IO twice, and to sort of try and get a handle on generalizing this outcome

if the producer doesn't need to open the file, then this doesn't save anything on either side

