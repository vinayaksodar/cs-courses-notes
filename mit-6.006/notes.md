# Lecture 1

Order of increasing asymtotic complexity
| Shorthand | Constant | Logarithmic | Linear | Quadratic | Polynomial | Exponential |
| --- | --- | --- | --- | --- | --- | --- |
| Θ(f(n)) | Θ(1) | Θ(log n) | Θ(n) | Θ(n^2) | Θ(n^c) | 2^Θ(n^c) |

In order to precisely calculate the resources used by an algorithm, we need to model how long a computer takes to perform basic operations. Specifying such a set of operations provides a model of computation upon which we can base our analysis. In this class, we will use the w-bit Word- RAM model of computation, which models a computer as a random access array of machine words called memory, together with a processor that can perform operations on the memory.

If a machine word contains only w bits, the processor will only be able to read and write from at most 2w addresses in memory2. So when solving a problem on an input stored in n machine words, we will always assume our Word-RAM has a word size of at least w > log2 n bits, or else the machine would not be able to access all of the input in memory.

We moved from 32 to 64 bit as 32 bit limited ram memory to 4gb

### Data Structure

A data structure is a way to store a non-constant amount of data, supporting a set of operations to interact with that data. The set of operations supported by a data structure is called an interface. Many data structures might support the same interface, but could provide different performance for each operation.

# Lecture 2

### Sequence Interface (L02, L07)

Sequences maintain a collection of items in an **extrinsic order**, where each item stored has a rank in the sequence, including a **first item** and a **last item**. By extrinsic, we mean that the first item is ‘first’, not because of what the item is, but because some external party put it there.

Sequences are generalizations of **stacks** and **queues**, which support a subset of sequence operations.

#### Sequence Operations

| **Container**     | **Static**                                              | **Dynamic** |
| ----------------- | ------------------------------------------------------- | ----------- |
| `build(X)`        | Given an iterable `X`, build sequence from items in `X` |
| `len()`           | Return the number of stored items                       |
| `iter_seq()`      | Return the stored items one-by-one in sequence order    |
| `get_at(i)`       | Return the `i`-th item                                  |
| `set_at(i, x)`    | Replace the `i`-th item with `x`                        |
| `insert_at(i, x)` | Add `x` as the `i`-th item                              |
| `delete_at(i)`    | Remove and return the `i`-th item                       |
| `insert_first(x)` | Add `x` as the first item                               |
| `delete_first()`  | Remove and return the first item                        |
| `insert_last(x)`  | Add `x` as the last item                                |
| `delete_last()`   | Remove and return the last item                         |

> **Note:** Insert/delete operations change the rank of all items after the modified item.

---

### Set Interface (L03-L08)

By contrast, **Sets** maintain a collection of items based on an **intrinsic property** involving what the items are, usually based on a **unique key** `x.key`, associated with each item `x`.

Sets are generalizations of **dictionaries** and other intrinsic query databases.

#### Set Operations

| **Container**  | **Static**                                                           | **Dynamic** | **Order** |
| -------------- | -------------------------------------------------------------------- | ----------- | --------- |
| `build(X)`     | Given an iterable `X`, build set from items in `X`                   |
| `len()`        | Return the number of stored items                                    |
| `find(k)`      | Return the stored item with key `k`                                  |
| `insert(x)`    | Add `x` to set (replace item with key `x.key` if one already exists) |
| `delete(k)`    | Remove and return the stored item with key `k`                       |
| `iter_ord()`   | Return the stored items one-by-one in key order                      |
| `find_min()`   | Return the stored item with the smallest key                         |
| `find_max()`   | Return the stored item with the largest key                          |
| `find_next(k)` | Return the stored item with the smallest key larger than `k`         |
| `find_prev(k)` | Return the stored item with the largest key smaller than `k`         |

> **Note:** `find` operations return `None` if no qualifying item exists.

---

#### Worst-Case Complexity Table for Some Sequence Data Structures

<table>
  <tr>
    <th rowspan="2">Data Structure</th>
    <th colspan="1">
    <th colspan="1">Static Operations</th>
    <th colspan="3">Dynamic Operations</th>
  </tr>
  <tr>
    <th>build(X)</th>
    <th>get_at(i), set_at(i, x)</th>
    <th>insert_first(x), delete_first()</th>
    <th>insert_last(x), delete_last()</th>
    <th>insert_at(i, x), delete_at(i)</th>
  </tr>
  <tr>
    <td>Array</td>
    <td>O(n)</td>
    <td>O(1)</td>
    <td>O(n)</td>
    <td>O(n)</td>
    <td>O(n)</td>
  </tr>
  <tr>
    <td>Linked List</td>
    <td>O(n)</td>
    <td>O(n)</td>
    <td>O(1)</td>
    <td>O(n)</td>
    <td>O(n)</td>
  </tr>
  <tr>
    <td>Dynamic Array</td>
    <td>O(n)</td>
    <td>O(1)</td>
    <td>O(1)</td>
    <td>O(1) (amortized)</td>
    <td>O(n)</td>
  </tr>
</table>
