=====================
Day 1: Not Quite Lisp
=====================

--- Part One ---
================

Day 1 is pretty simple: iterate over each char of the input puzzle string.

.. code-block:: c

   for (unsigned i = 0; i < strlen(puzzle); ++i) {
     /* puzzle[i] */
   }

Increment/Decrement a counter to keep the current floor.

.. code-block:: c

    if (puzzle[i] == '(') {
      ++floor;
    } else if (puzzle[i] == ')') {
      --floor;
    } else {
      abort();
    }

--- Part Two ---
================

We only have to add a break statement in the main loop when the floor -1 is reached.

.. code-block:: c

   if (floor == -1) {
     printf("> basement: %u\n", i + 1);
     break;
   }
