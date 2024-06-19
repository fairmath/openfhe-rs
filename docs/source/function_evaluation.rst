Arbitrary smooth function evaluation in CKKS via OpenFHE-rs
===========================================================

Overview
--------

This document describes how to evaluate an arbitrary smooth function on a ciphertext in CKKS using `Chebyshev approximation <https://www.gnu.org/software/gsl/doc/html/cheb.html>`_.
The Chebyshev approximation is a method of approximating a smooth function using polynomials, see more `on Wiki <https://en.wikipedia.org/wiki/Chebyshev_polynomials>`_.

Rust example
------------

The example for this code is located in `examples/function_evaluation.rs <https://github.com/fairmath/openfhe-rs/blob/master/examples/function_evaluation.rs>`_.
The file gives examples of how to run `EvalLogistic`, the logistic function $\frac{1}{1 + e^{-x}}$, and an arbitrary function using `EvalChebyshevFunction`.
We use the square root function in our example for `EvalChebyshevFunction`.

Input parameters
----------------

Our Rust wrapper is based on the original OpenFHE interface; `EvalLogistic` function requires the following input parameters:

- `ciphertext`: the ciphertext we wish to operate on.
- `a`: the lower bound of underlying plaintext values we could have.
- `b`: the upper bound of underlying plaintext values we could have.
- `degree`: the desired polynomial degree of the Chebyshev approximation.
  A higher degree gives a more precise estimate but takes longer to run.

Running the example
~~~~~~~~~~~~~~~~~~~~

1. Ensure the `openfhe-rs` library is installed and properly configured, see the :doc:`intro` section.
2. Go to the `openfhe-rs` directory.
3. Compile and run the `function_evaluation.rs` example:

.. code-block:: sh

    cargo run --example function_evaluation

This should output the results of the homomorphic computations to the console.

How to choose a multiplicative depth
-------------------------------------

Each run of `EvalChebyshevFunction` requires a certain number of multiplications which depends on the input polynomial degree.
We provide a table below to map polynomial degrees to multiplicative depths.

+-------------+---------------------+
| Degree      | Multiplicative Depth|
+=============+=====================+
| 3-5         | 4                   |
+-------------+---------------------+
| 6-13        | 5                   |
+-------------+---------------------+
| 14-27       | 6                   |
+-------------+---------------------+
| 28-59       | 7                   |
+-------------+---------------------+
| 60-119      | 8                   |
+-------------+---------------------+
| 120-247     | 9                   |
+-------------+---------------------+
| 248-495     | 10                  |
+-------------+---------------------+
| 496-1007    | 11                  |
+-------------+---------------------+
| 1008-2031   | 12                  |
+-------------+---------------------+

Note that for a range $(a, b) = (-1, 1)$, the multiplicative depth is 1 less than the depths listed in the table.

