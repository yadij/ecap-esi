
# eCAP library for Edge Side Include (ESI) Surrogate

## REQMOD adaptation service

This library provides a REQMOD service
 `ecap://ecap-esi/0.0.1/surrogate` which adds
 `Surrogate-Capability: "ESI/1.0"` headers on server traffic.

This service is enabled by default in the provided
Squid configuration file `ecap-esi.conf`.


# Compile and Build

## Requirements

 * cmake toolchain
 * A C++17 compiler
 * libecap version 1.0.0 or later

## Bootstrap with cmake

 `cmake -DCMAKE_INSTALL_PREFIX:PATH=/ .`

## Build and Install with make

 `make install`

