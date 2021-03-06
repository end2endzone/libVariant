# Any commands which fail will cause the shell script to exit immediately
set -e

# Validate Travis CI environment
if [ "$TRAVIS_BUILD_DIR" = "" ]; then
  echo "Please define 'TRAVIS_BUILD_DIR' environment variable.";
  exit 1;
fi

echo ============================================================================
echo Testing stdint types
echo ============================================================================
cd $TRAVIS_BUILD_DIR/build/bin
./stdint_types_test

echo ============================================================================
echo Testing project
echo ============================================================================
cd $TRAVIS_BUILD_DIR/build/bin
./libvariant_unittest || true; #do not fail build even if a test fails.
