/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <queue>
#include "subt_gazebo/FlashLightPlugin.hh"
#include "subt_gazebo/protobuf/lightcommand.pb.h"
#include "gazebo/common/Time.hh"

namespace gazebo
{
  /// \brief An example usage of FlashLightPlugin class
  // This sample plugin just waits for 10 seconds,
  // then it turns on all lights.
  class LightControlPlugin : public FlashLightPlugin
  {
    /// \brief Called when the plugin is loaded.
    //  It sets the time to wait.
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

    /// \brief Called when the world is updated
    //  It counts down as it checks the simulation time.
    //  When the count gets zero, it turns on the lights.
    public: void OnUpdate();

    /// \brief Process all incoming messages.
    private: void ProcessIncomingMsgs();

    /// \brief Callback executed when a new request is received.
    /// \param _req The light command contained in the request.
    private: void OnMessage(const subt::msgs::LightCommand &_req);

    /// \brief Connection to World Update events.
    private: event::ConnectionPtr updateConnection;

    /// \brief An Ignition Transport node for communications.
    private: ignition::transport::Node node;

    /// \brief Collection of incoming messages received during the last
    /// simulation step.
    private: std::queue<subt::msgs::LightCommand> incomingMsgs;

    /// \brief Protect data from races.
    private: std::mutex mutex;
  };
}