class PriorityQueue:
    def __init__(self, A):
        self.A = []

    def insert(self, x):
        """
        Insert an element x into the priority queue.

        Args:
            x: The element to be inserted into the priority queue.
        """

        self.A.append(x)

    def delete_max(self):
        if len(self.A) < 1:
            raise IndexError("pop from empty priority queue")
        return self.A.pop()

    @classmethod
    def sort(Queue, A):
        pq = Queue(A)
        for x in A:
            pq.insert(x)
        out = [pq.delete_max() for i in range(len(A))]
        out.reverse()
        return out


class PQ_Array(PriorityQueue):
    def delete_max(self):
        # Swap max element with the last element of the array
        max_element_index = 0
        for i in range(1, len(self.A)):
            if self.A[i] > self.A[i - 1]:
                max_element_index = i
        self.A[max_element_index], self.A[-1] = self.A[-1], self.A[max_element_index]
        return super().delete_max()


class PQ_Heap(PriorityQueue):
    def insert(self, *args):
        super.insert(*args)
        n, A = len(self.A), self.A
        self.max_heapify_up(A, n, n - 1)

    def max_heapify_up(self, A, n, c):
        p = parent(c)
        if A[p] < A[c]:
            A[c], A[p] = A[p], A[c]
            self.max_heapify_up(A, n, p)
