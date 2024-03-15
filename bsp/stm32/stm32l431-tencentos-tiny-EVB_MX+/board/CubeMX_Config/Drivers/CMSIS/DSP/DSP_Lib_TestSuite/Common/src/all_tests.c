#include "jtest.h"
#include "basic_math_test_group.h"
#include "complex_math_test_group.h"
#include "controller_test_group.h"
#include "fast_math_test_group.h"
#include "filtering_test_group.h"
#include "matrix_test_group.h"
#include "statistics_test_group.h"
#include "support_test_group.h"
#include "transform_test_group.h"
#include "intrinsics_test_group.h"

JTEST_DEFINE_GROUP(all_tests)
{
  /*
    To skip a test, comment it out
  */
#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_BASICMATH_TESTS)
  JTEST_GROUP_CALL(basic_math_tests);
#endif 

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_COMPLEXMATH_TESTS)
  JTEST_GROUP_CALL(complex_math_tests);
#endif

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_CONTROLLER_TESTS)
  JTEST_GROUP_CALL(controller_tests);
#endif

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_FASTMATH_TESTS)
  JTEST_GROUP_CALL(fast_math_tests);
#endif

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_FILTERING_TESTS)
  /* Biquad df2T_f32 will fail with Neon. The test must be updated.
  Neon implementation is requiring a different initialization.
  */
  JTEST_GROUP_CALL(filtering_tests);
#endif

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_MATRIX_TESTS)
  JTEST_GROUP_CALL(matrix_tests);
#endif 

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_STATISTICS_TESTS)
  JTEST_GROUP_CALL(statistics_tests);
#endif()

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_SUPPORT_TESTS)
  JTEST_GROUP_CALL(support_tests);
#endif

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_TRANSFORM_TESTS)
  JTEST_GROUP_CALL(transform_tests);
#endif

#if !defined(CUSTOMIZE_TESTS) || defined(ENABLE_INTRINSICS_TESTS)
  JTEST_GROUP_CALL(intrinsics_tests);
#endif

  return;
}
