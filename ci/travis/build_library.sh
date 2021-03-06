# Any commands which fail will cause the shell script to exit immediately
set -e

# Validate Travis CI environment
if [ "$TRAVIS_BUILD_DIR" = "" ]; then
  echo "Please define 'TRAVIS_BUILD_DIR' environment variable.";
  exit 1;
fi

export GTEST_ROOT=$TRAVIS_BUILD_DIR/third_parties/googletest/install
export INSTALL_LOCATION=$TRAVIS_BUILD_DIR/install

echo ============================================================================
echo Generating...
echo ============================================================================
cd $TRAVIS_BUILD_DIR
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_LOCATION -DLIBVARIANT_BUILD_TEST=ON -DBUILD_SHARED_LIBS=OFF -DLIBVARIANT_BUILD_STDINT_TYPES_TEST=ON -DLIBVARIANT_USE_STD_STRING=$LIBVARIANT_USE_STD_STRING ..

echo ============================================================================
echo Compiling...
echo ============================================================================
cmake --build .
echo

echo ============================================================================
echo Installing into $INSTALL_LOCATION
echo ============================================================================
make install
echo

# Delete all temporary environment variable created
unset GTEST_ROOT
unset INSTALL_LOCATION
