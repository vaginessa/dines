#!/bin/bash

# before lauching this, run
# ./configure --enable-gcov

make -j && \
./test_dines && \
sudo ./test_root_dines && \
./tests/live_tests.sh && \
lcov -c --directory src --output-file coverage.info && \
genhtml coverage.info --output-directory dines_html
