---
description: >-
  Brings together researchers and developers to solve real-world cryptography
  problems
---

FHERMA is a platform for Fully Homomorphic Encryption (FHE) challenges, jointly developed by **Fair Math** and the **OpenFHE** teams.

The main goal of the project is to develop an open-source library of FHE components. Such a library can significantly simplify application development and accelerate the adoption of FHE. The initial focus will be on components for **Machine Learning** and **Blockchain** applications.

## Challenges

On the platform, there are two types of challenges:

1. **Black Box:** In this type of challenge, participants develop solutions according to the challenge requirements, process encrypted test data, and submit to the platform only the serialized final ciphertext. This type of challenge does not require submitting source code or any other data that reveals the details of the solution itself. The main criterion for evaluating and ranking solutions in this type of challenge is accuracy.

2. **White Box:** It is not possible to evaluate the performance of the solution based solely on the ciphertext. While the Black Box type is suitable for many challenges, for others, it is crucial to obtain the most efficient solution from a performance perspective. For these, the White Box type is available. Participants are required to submit the source code of their projects to the platform. The platform will compile the project and run tests to measure performance and accuracy. The main criteria for evaluating and ranking solutions in this type of challenge are performance and accuracy. Solutions uploaded to the platform are confidential and are not available to other participants.

Challenges on FHERMA are being solved using one of three languages:

* Go - using [Lattigo](https://github.com/tuneinsight/lattigo)
* Python - using [openfhe-python](https://github.com/openfheorg/openfhe-python)
* Rust - using [openfhe-rs](https://crates.io/crates/openfhe)
* C++ - using [openfhe](https://www.openfhe.org/)

We collect winning solutions and put them into the open-source repository [Polycircuit](https://github.com/fairmath/polycircuit).
