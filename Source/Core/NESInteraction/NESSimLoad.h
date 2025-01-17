//===========================================================//
// This file is part of the BrainGenix-EVM Validation System //
//===========================================================//

/*
    Description: This file provides system loading via NES.
    Additional Notes: None
    Date Created: 2024-04-22
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
//#include <nlohmann/json.hpp>


// Internal Libraries (BG convention: use <> instead of "")
#include <RPC/SafeClient.h>

#include <BG/Common/Logger/Logger.h>


namespace BG {


enum BGStatusCode {
    BGStatusSuccess = 0,
    BGStatusGeneralFailure = 1,
    BGStatusInvalidParametersPassed = 2,
    BGStatusUpstreamGatewayUnavailable = 3,
    BGStatusUnauthorizedInvalidNoToken = 4,
    BGStatusSimulationBusy = 5,
    NUMBGStatusCode
};



bool GetNESStatus(BG::Common::Logger::LoggingSystem* _Logger, SafeClient& _Client, BGStatusCode& _StatusCode);

bool AwaitNESOutcome(BG::Common::Logger::LoggingSystem* _Logger, SafeClient& _Client, unsigned long _Timeout_ms = 100000);

/**
 * Ask NES to load a previously saved simulation and wait for loading
 * to complete or fail.
 * 
 * @param _Client Reference to client connection with NES.
 * @param _SimSaveName Name of the previously saved simulation.
 * @param _SimID Reference through which to return the simulation ID.
 * @param _Timeout_ms Timeout that ensures this function cannot become stuck forever (e.g. due to broken connection),
 * @return True if loading was successful.
 */
bool AwaitNESSimLoad(BG::Common::Logger::LoggingSystem* _Logger, SafeClient& _Client, const std::string& _SimSaveName, int& _SimID, unsigned long _Timeout_ms = 100000);

} // BG
