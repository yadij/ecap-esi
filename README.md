
# eCAP library for Edge Side Include (ESI) Surrogate

## REQMOD adaptation service

From version 0.0.1 this library provides a REQMOD service
 `ecap://@PROJECT_NAME@/@PROJECT_VERSION@/surrogate` which adds
 `Surrogate-Capability: "ESI/1.0"` headers on server traffic.

This service is enabled by default in the provided
`ecap-esi.conf` file.

# Compile and Build

## Requirements

 * cmake toolchain
 * A C++17 compiler
 * libecap version 1.0.0 or later

## Bootstrap with cmake

 `cmake -DCMAKE_INSTALL_PREFIX:PATH=/ .`

## Build and Install with make

 `make install`

