/*
 *   test_toolkitAPI_gage.cpp
 *
 *   Created: 03/10/2018
 *   Author: Bryant E. McDonnell
 *           EmNet LLC
 *
 *   Unit testing mechanics for the gage API using Boost Test.
 */

 #include <boost/test/unit_test.hpp>

 #include "test_solver.hpp"


#define ERR_NONE 0

BOOST_AUTO_TEST_SUITE(test_toolkitapi_gage_fixture)

// Testing Rain Gage Setter
BOOST_FIXTURE_TEST_CASE(get_set_gage_rate, FixtureBeforeStep){
    int error, step_ind;
    int rg_ind, subc_ind;
    double rain, rainfall, snowfall, total_precipitation;
    double elapsedTime = 0.0;

    double start_rainfall_rate = 0;     // in/hr
    double new_rainfall_rate = 4.2;     // in/hr
    double total_rainfall_volume;       // in

    char rgid[] = "RG1";
    char subid[] = "1";

    error = swmm_getObjectIndex(SM_GAGE, rgid, &rg_ind);
    BOOST_REQUIRE(error == ERR_NONE);
    error = swmm_getObjectIndex(SM_SUBCATCH, subid, &subc_ind);
    BOOST_REQUIRE(error == ERR_NONE);

    step_ind = 0;
    do
    {
        if (step_ind == 0) // (Jan 1, 1998 12:00am)
        {
            error = swmm_setGagePrecip(rg_ind, 0);
            BOOST_REQUIRE(error == ERR_NONE);
        }
        if (step_ind == 360) // (Jan 1, 1998 6:00am)
        {
            // Gage
            error = swmm_getGagePrecip(rg_ind, SM_RAINFALL, &rainfall);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(rainfall - start_rainfall_rate, 0.0001);
            error = swmm_getGagePrecip(rg_ind, SM_SNOWFALL, &snowfall);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(snowfall - 0.0, 0.0001);
            error = swmm_getGagePrecip(rg_ind, SM_TOTALPRECIP, &total_precipitation);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(total_precipitation - start_rainfall_rate, 0.0001);

            // Subcatchment
            error = swmm_getSubcatchResult(subc_ind, SM_SUBCRAIN, &rain);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(rain - start_rainfall_rate, 0.0001);

            // Setting Rainfall Rate
            error = swmm_setGagePrecip(rg_ind, new_rainfall_rate);
            BOOST_REQUIRE(error == ERR_NONE);
        }

        if (step_ind == 720) // (Jan 1, 1998 12:00pm)
        {
            // Gage
            error = swmm_getGagePrecip(rg_ind, SM_RAINFALL, &rainfall);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(rainfall - start_rainfall_rate, 0.0001);
            error = swmm_getGagePrecip(rg_ind, SM_SNOWFALL, &snowfall);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(snowfall - 0.0, 0.0001);
            error = swmm_getGagePrecip(rg_ind, SM_TOTALPRECIP, &total_precipitation);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(total_precipitation - start_rainfall_rate, 0.0001);

            // Subcatchment
            error = swmm_getSubcatchResult(subc_ind, SM_SUBCRAIN, &rain);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(rain - new_rainfall_rate, 0.0001);

            // Setting Rainfall Rate
            error = swmm_setGagePrecip(rg_ind, start_rainfall_rate);
            BOOST_REQUIRE(error == ERR_NONE);
        }

        // Route Model Forward
        error = swmm_step(&elapsedTime);
        BOOST_REQUIRE(error == ERR_NONE);

        step_ind+=1;
    }while (elapsedTime != 0 && !error);


    // Final Checks from Subcatchment Stats Totalizers
    SM_SubcatchStats *subc_stats = NULL;

    error = swmm_getSubcatchStats(subc_ind, &subc_stats);
    BOOST_CHECK_EQUAL(error, ERR_NONE);
    // 4.2 in/hr * 6hrs = 25.2 inches
    total_rainfall_volume = new_rainfall_rate * 6;
    // Time to call FEMA!
    BOOST_CHECK_SMALL(subc_stats->precip - total_rainfall_volume, 0.0001);

    swmm_freeMemory(subc_stats);

    swmm_end();
}


BOOST_AUTO_TEST_SUITE_END()
