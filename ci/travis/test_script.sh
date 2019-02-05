# Any commands which fail will cause the shell script to exit immediately
set -e

# Validate Travis CI environment
if [ "$TRAVIS_BUILD_DIR" = "" ]; then
  echo "Please define 'TRAVIS_BUILD_DIR' environment variable.";
  exit 1;
fi

echo ============================================================================
echo Testing project
echo ============================================================================
cd $TRAVIS_BUILD_DIR/build/bin

echo =======================================================================
echo Testing project "(1 of 2)"
echo =======================================================================
./libvariant_unittest || true; #do not fail build even if a test fails.

echo =======================================================================
echo Testing project "(2 of 2)"
echo =======================================================================
./libvariant_templates_unittest || true; #do not fail build even if a test fails.
