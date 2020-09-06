/*
 *   test_toolkitAPI_pollut.cpp
 *
 *   Created: 07/20/2018
 *   Author: Katherine M. Ratliff
 *   
 *   Edited: 08/13/2020
 *   Author: Abhiram Mullapudi
 *
 *   Unit testing mechanics for the pollutant API using Boost Test.
 */

 #include <boost/test/unit_test.hpp>
 #include "test_pollutants.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(test_toolkitapi_pollut)

// Testing Pollutant Getter
BOOST_FIXTURE_TEST_CASE(get_pollut_values, FixtureBeforeStep){
    int error, step_ind;
    int subc_ind;
    int node_ind;
    int link_ind;
    double* buildup_array;
    double* ponded_array;
    double* runoff_qual;
    double* runoff_load;
    double* node_qual;
    double* link_qual;
    double* link_load;
    double elapsedTime = 0.0;
    // Pollutant IDs
    int TSS = 0;
    int Lead = 1;

    string subid = string("1");
    string nodeid = string("9");
    string linkid = string("1");

    error = swmm_getObjectIndex(SM_SUBCATCH, (char *)subid.c_str(), &subc_ind);
    BOOST_REQUIRE(error == ERR_NONE);

    error = swmm_getObjectIndex(SM_NODE, (char *)nodeid.c_str(), &node_ind);
    BOOST_REQUIRE(error == ERR_NONE);

    error = swmm_getObjectIndex(SM_LINK, (char *)linkid.c_str(), &link_ind);
    BOOST_REQUIRE(error == ERR_NONE);

    step_ind = 0;

    do
    {
        if (step_ind == 360) // (Jan 1, 1998 6:00am)
        {
            // subcatchment buildup
            error = swmm_getSubcatchPollut(subc_ind, SM_BUILDUP, &buildup_array);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(buildup_array[TSS] - 31.906912, 0.0001);
            BOOST_CHECK_SMALL(buildup_array[Lead] - 0.0, 0.0001);

            // subcatchment ponded concentration
            error = swmm_getSubcatchPollut(subc_ind, SM_CPONDED, &ponded_array);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(ponded_array[TSS] - 0.0, 0.0001);
            BOOST_CHECK_SMALL(ponded_array[Lead] - 0.0, 0.0001);

            // subcatchment runoff pollutant concentration
            error = swmm_getSubcatchPollut(subc_ind, SM_SUBCQUAL, &runoff_qual);
            BOOST_CHECK_SMALL(runoff_qual[TSS] - 14.118948, 0.0001);
            BOOST_CHECK_SMALL(runoff_qual[Lead] - 2.823790, 0.0001);

            // subcatchment runoff total pollutant loading
            error = swmm_getSubcatchPollut(subc_ind, SM_SUBCTOTALLOAD, &runoff_load);
            BOOST_CHECK_SMALL(runoff_load[TSS] - 0.00242786, 0.0001);
            BOOST_CHECK_SMALL(runoff_load[Lead] - 4.856e-10, 0.0001);

            // node pollutant concentration
            error = swmm_getNodePollut(node_ind, SM_NODEQUAL, &node_qual);
            BOOST_CHECK_SMALL(node_qual[TSS] - 14.121316, 0.0001);
            BOOST_CHECK_SMALL(node_qual[Lead] - 2.824263, 0.0001);

            // link pollutant concentration
            error = swmm_getLinkPollut(node_ind, SM_LINKQUAL, &link_qual);
            BOOST_CHECK_SMALL(link_qual[TSS] - 14.124621, 0.0001);
            BOOST_CHECK_SMALL(link_qual[Lead] - 2.824924, 0.0001);

            // link pollutant total load
            error = swmm_getLinkPollut(node_ind, SM_TOTALLOAD, &link_load);
            BOOST_CHECK_SMALL(link_load[TSS] - 38.496695, 0.01);
            BOOST_CHECK_SMALL(link_load[Lead] - 0.00769934, 0.0001);
        }

        if (step_ind == 720) // (Jan 1, 1998 12:00pm)
        {
            // subcatchment buildup
            error = swmm_getSubcatchPollut(subc_ind, SM_BUILDUP, &buildup_array);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(buildup_array[TSS] - 32.354460, 0.0001);
            BOOST_CHECK_SMALL(buildup_array[Lead] - 0.0, 0.0001);

            // subcatchment ponded concentration
            error = swmm_getSubcatchPollut(subc_ind, SM_CPONDED, &ponded_array);
            BOOST_REQUIRE(error == ERR_NONE);
            BOOST_CHECK_SMALL(ponded_array[TSS] - 0.0, 0.0001);
            BOOST_CHECK_SMALL(ponded_array[Lead] - 0.0, 0.0001);

            // subcatchment runoff pollutant concentration
            error = swmm_getSubcatchPollut(subc_ind, SM_SUBCQUAL, &runoff_qual);
            BOOST_CHECK_SMALL(runoff_qual[TSS] - 0.0, 0.0001);
            BOOST_CHECK_SMALL(runoff_qual[Lead] - 0.0, 0.0001);

            // subcatchment runoff total pollutant loading
            error = swmm_getSubcatchPollut(subc_ind, SM_SUBCTOTALLOAD, &runoff_load);
            BOOST_CHECK_SMALL(runoff_load[TSS] - 0.00248221, 0.0001);
            BOOST_CHECK_SMALL(runoff_load[Lead] - 4.964e-10, 0.0001);

            // node pollutant concentration
            error = swmm_getNodePollut(node_ind, SM_NODEQUAL, &node_qual);
            BOOST_CHECK_SMALL(node_qual[TSS] - 0.0, 0.0001);
            BOOST_CHECK_SMALL(node_qual[Lead] - 0.0, 0.0001);

            // link pollutant concentration
            error = swmm_getLinkPollut(node_ind, SM_LINKQUAL, &link_qual);
            BOOST_CHECK_SMALL(link_qual[TSS] - 4.380e-11, 0.0001);
            BOOST_CHECK_SMALL(link_qual[Lead] - 8.759e-12, 0.0001);

            // link pollutant total load
            error = swmm_getLinkPollut(node_ind, SM_TOTALLOAD, &link_load);
            BOOST_CHECK_SMALL(link_load[TSS] - 39.780193, 0.01);
            BOOST_CHECK_SMALL(link_load[Lead] - 0.00795604, 0.0001);
        }

        // Route Model Forward
        error = swmm_step(&elapsedTime);
        step_ind+=1;
    }while (elapsedTime != 0 && !error);
    BOOST_REQUIRE(error == ERR_NONE);

    freeArray((void**) &buildup_array);
    freeArray((void**) &ponded_array);

    swmm_end();
}

// Testing Node influent - storage assets
BOOST_FIXTURE_TEST_CASE(get_node_pollutant_values_cin, FixtureBeforeStep_Pollut_Node){
    
    int error, step_ind;
    double* node_qual;
    double elapsedTime = 0.0;
    double total_pollutant = 0.0;

    // Pollutant IDs
    int P1 = 0;
    double cin = 10;

    step_ind = 0;
    do
    {
 	
	error = swmm_getNodePollut(1, SM_NODECIN, &node_qual);
	BOOST_REQUIRE(error == ERR_NONE);

	// Check for constant influent
	if (step_ind > 5) BOOST_CHECK_SMALL(cin - node_qual[P1], 0.00);

	// Route Model Forward
        error = swmm_step(&elapsedTime);
        step_ind+=1;

    }while (elapsedTime != 0 && !error);
    BOOST_REQUIRE(error == ERR_NONE);
    
    swmm_end();
}

// Testing Reactor Concentration
BOOST_FIXTURE_TEST_CASE(get_node_reactor_pollutant, FixtureBeforeStep_Pollut_Node){
    
    int error, step_ind;
    double* old_qual;
    double* new_qual;
    double elapsedTime = 0.0;
    double total_pollutant = 0.0;

    // Pollutant IDs
    int P1 = 0;

    step_ind = 0;
    do
    {	
	// Check for steady state after 1000 steps.
	// 1000 is a aribitarly long time duration, it can be any value as long 
	// the system reaches a steady state

	// Get reactor concentration
	error = swmm_getNodePollut(1, SM_NODECIN, &new_qual);
	BOOST_REQUIRE(error == ERR_NONE);

	if (step_ind > 1000)
	{
		BOOST_CHECK_SMALL(old_qual[P1] - new_qual[P1], 0.00);
	}
	
	old_qual = new_qual;

        // Route Model Forward
        error = swmm_step(&elapsedTime);
        step_ind+=1;
    }while (elapsedTime != 0 && !error);
    BOOST_REQUIRE(error == ERR_NONE);
    swmm_end();
}


// Testing Pollutant Setter - Node - Cumulative 
BOOST_FIXTURE_TEST_CASE(set_node_pollutant_cumulative_values, FixtureBeforeStep_Pollut_Node){
    
    int error;
    double* node_qual;
    double elapsedTime = 0.0;
    double total_pollutant = 0.0;

    // Pollutant IDs
    int P1 = 0;

    do
    {
	// Set pollutant
	error = swmm_setNodePollut(1, P1, 0);
	BOOST_REQUIRE(error == ERR_NONE);
	// Get pollutant
	error = swmm_getNodePollut(1, SM_NODEQUAL, &node_qual);
	BOOST_REQUIRE(error == ERR_NONE);
	// Record cumulative pollutant 
	total_pollutant = total_pollutant + node_qual[P1];
        // Route Model Forward
        error = swmm_step(&elapsedTime);
        
    }while (elapsedTime != 0 && !error);
    BOOST_REQUIRE(error == ERR_NONE);

    // Cumulative must be 0.00
    BOOST_CHECK_SMALL(total_pollutant, 0.00);
    swmm_end();
}

// Testing Pollutant Setter - Node - Stepwise 
BOOST_FIXTURE_TEST_CASE(set_node_pollutant_stepwise_values, FixtureBeforeStep_Pollut_Node){
    
    int error;
    double* node_qual;
    double elapsedTime = 0.0;

    // Pollutant IDs
    int P1 = 0;
    do
    {
	// Set pollutant
	error = swmm_setNodePollut(1, P1, 1.234);
	BOOST_REQUIRE(error == ERR_NONE);

	// Route Model Forward
        error = swmm_step(&elapsedTime);

	// Get pollutant
	error = swmm_getNodePollut(1, SM_NODEQUAL, &node_qual);
	BOOST_REQUIRE(error == ERR_NONE);

	// Check
    	BOOST_CHECK_SMALL(node_qual[P1] - 1.234, 0.00);

    }while (elapsedTime != 0 && !error);
    BOOST_REQUIRE(error == ERR_NONE);
    swmm_end();
}


// Testing Pollutant Setter - Link - Stepwise - overwrite
BOOST_FIXTURE_TEST_CASE(set_link_pollutant_stepwise_values_overwrite, FixtureBeforeStep_Pollut_Link){

    int error, link_ind, node_ind;
    int step;
    double* link_qual;
    double* node_qual;
    double elapsedTime = 0.0;
    double node_inflow;

    char linkid[] = "Culvert";
    char nodeid[] = "Outlet";


    // Pollutant ID
    int P1 = 0;

    error = swmm_getObjectIndex(SM_LINK, linkid, &link_ind);
    BOOST_REQUIRE(error == ERR_NONE);
    error = swmm_getObjectIndex(SM_NODE, nodeid, &node_ind);
    BOOST_REQUIRE(error == ERR_NONE);

    do
    {
	    // Set pollutant in link and check the pollutant in the node
	    error = swmm_setLinkPollut(link_ind, SM_LINKQUALSET, P1, 2.4563);
	    BOOST_REQUIRE(error == ERR_NONE);

	    // Route Model Forward
            error = swmm_step(&elapsedTime);
	    BOOST_REQUIRE(error == ERR_NONE);
	   
	    if (step > 2) // Wait for water to reach node
            { 
	    // Get infows concentration in node
            error = swmm_getNodePollut(node_ind,  SM_NODEQUAL, &node_qual);
	    BOOST_REQUIRE(error == ERR_NONE);

	    error = swmm_getLinkPollut(link_ind, SM_LINKQUAL, &link_qual);
	    
	    // Check
            BOOST_CHECK_SMALL(abs(node_qual[P1] - link_qual[P1]), 0.01);
    	    }
	    step += 1;

    }while (elapsedTime != 0 && !error);
    BOOST_REQUIRE(error == ERR_NONE);
    swmm_end();
}
BOOST_AUTO_TEST_SUITE_END()
