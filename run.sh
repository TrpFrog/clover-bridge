#!/bin/sh

cmake -B out .
cmake --build out
./out/clover-bridge
