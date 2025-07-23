# Software construction

## Magic numbers

Don't use random numbers like arr[100] what if input is greater than 100.  
Use numbers that make sense for example if you are dealing with alphabets <=26 is much better than <27 as 26 makes it more readable in this context.

## Testing

No code is 100% bug free no matter how many tests you write.
[A good resource on testing](https://ocw.mit.edu/ans7870/6/6.005/s16/classes/03-testing/) - covers how methodologies, partitioning the input space and best practices.

## Code review

    Don’t Repeat Yourself (DRY)
    Comments where needed
        - Specifications above methods
        - Refernce sources StackOverflow, Youtube etc
    Fail fast
        - Raise exceptions closest to cause
    Avoid magic numbers
    One purpose for each variable
    Use good names
        - Don't use names like tmp
    No global variables
    

## Specification

### Specification structure

A specification of a method consists of several clauses:

a precondition , indicated by the keyword requires
a postcondition , indicated by the keyword effects
The precondition is an obligation on the client (i.e., the caller of the method). It’s a condition over the state in which the method is invoked.

The postcondition is an obligation on the implementer of the method. If the precondition holds for the invoking state, the method is obliged to obey the postcondition, by returning appropriate values, throwing specified exceptions, modifying or not modifying objects, and so on.

So a specification like this:

    static int find(int[] arr, int val)
    requires: val occurs exactly once in arr
    effects:  returns index i such that arr[i] = val
… might be rendered in Java like this:

    ```java
    /**
     * Find a value in an array.
     * @param arr array to search, requires that val occurs exactly once
     *            in arr
     * @param val value to search for
     * @return index i such that arr[i] = val
     */
    static int find(int[] arr, int val)
    ```

Avoid null in specification and also mention mutation of any inputs or side effects explicitly

### Testing specification

Your implementation may provide stronger guarantees than the specification calls for, or it may have specific behavior where the specification is undefined. But your test cases should not count on that behavior. Test cases must obey the contract, just like every other client.

## Exceptions

You are only concerned with Exceptions and Assertions

Error is a subclass of Throwable that is reserved for errors produced by the Java runtime system, such as StackOverflow­Error and OutOfMemory­Error . For some reason Assertion­Error also extends Error , even though it indicates a bug in user code, not in the runtime. Errors should be considered unrecoverable, and are generally not caught.

You should use an unchecked exception only to signal an unexpected failure (i.e. a bug), or if you expect that clients will usually write code that ensures the exception will not happen, because there is a convenient and inexpensive way to avoid the exception;
Otherwise you should use a checked exception.

## Assertions

They are usually used only in debugging and removed in productions. Use them to check the LOGIC of our codes, not where it fails for example if you expect an array to be sorted by at some point in the code or say x<0 in some point in the code.

Purpose: Validate assumptions about internal program logic that should always hold true if the code is correct.

## Mutability and Immutability

Aliasing—having multiple references to the same mutable object—is problematic, especially when caching or when the object is mutated elsewhere in the code while you still assume it's unchanged.

This can be addressed by:

1. Returning a copy of the object instead of mutating the original. However, this may lead to unnecessary copies, even if the returned copy is never modified.
2. Returning an immutable object. This ensures that if the object needs to be modified later, a new object is created, while existing references continue to point to the original, avoiding unintended side effects.

## Recursion vs iteration

The main reason to use recursion is to take more advantage of immutability. In an ideal recursive implementation, all variables are final, all data is immutable, and the recursive methods are all pure functions in the sense that they do not mutate anything. The behavior of a method can be understood simply as a relationship between its parameters and its return value, with no side effects on any other part of the program. This kind of paradigm is called functional programming , and it is far easier to reason about than imperative programming with loops and variables.

The main downside of recursion is that it may take more space than an iterative solution. Building up a stack of recursive calls consumes memory temporarily, and the stack is limited in size, which may become a limit on the size of the problem that your recursive implementation can solve.

