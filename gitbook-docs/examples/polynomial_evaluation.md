# Polynomial evaluation in CKKS via OpenFHE-rs

For license information, refer to the [License file](../../LICENSE).

## About

This document describes how to call polynomial evaluation on a ciphertext in CKKS.
Polynomial evaluation refers to the computation of the value of a polynomial when its indeterminates are substituted for some values, see more [on Wiki](https://en.wikipedia.org/wiki/Polynomial_evaluation).

## Rust example

The example for this code is located in [examples/polynomial_evaluation.rs](../../examples/polynomial_evaluation.rs).
This code gives an example of how to run `EvalPoly` function and outputs in the log input parameters, the result of evaluation and the evaluation time

## Input parameters

Our Rust wrapper is based on the original OpenFHE interface; `EvalPoly` function requires the following input parameters:

- `ciphertext`: the ciphertext we wish to operate on.
- `coefficients`: the coefficients to run polynomial evaluation upon, vector array of doubles.
In this example, we run the evaluation upon two sets of coefficients:
    1. {0.15, 0.75, 0, 1.25, 0, 0, 1, 0, 1, 2, 0, 1, 0, 0, 0, 0, 1}
    2. {1, 2, 3, 4, 5, -1, -2, -3, -4, -5, 0.1, 0.2, 0.3, 0.4, 0.5, -0.1, -0.2, -0.3, -0.4, -0.5, 0.1, 0.2, 0.3, 0.4, 0.5, -0.1, -0.2, -0.3, -0.4, -0.5}.

For this example, we set the multiplicative depth at 6 and scaling mod size at 50.
