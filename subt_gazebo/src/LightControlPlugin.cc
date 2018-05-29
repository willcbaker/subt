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

#include "subt_gazebo/LightControlPlugin.hh"

using namespace gazebo;

//////////////////////////////////////////////////
LightControlPlugin::LightControlPlugin(): FlashLightPlugin(), count{10}
{
}

//////////////////////////////////////////////////
void LightControlPlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
  // === must call this ===
  FlashLightPlugin::Load(_parent, _sdf);

  // === User's code goes here ===
  gzmsg << "Plugin Loaded: LightControlPlugin\n" << std::endl;
  this->world = _parent->GetWorld();
  start_time = this->world->SimTime();
  this->count = 10;
  gzmsg << this->count << " sec to turn on..." << std::endl;
  this->TurnOffAll();
}

//////////////////////////////////////////////////
void LightControlPlugin::OnUpdate()
{
  // === must call this ===
  FlashLightPlugin::OnUpdate();

  // === User's code goes here ===
  common::Time current_time = this->world->SimTime();
  if (current_time.Double() - this->start_time.Double() > 1.0)
  {
    this->count--;
    this->start_time = current_time;
    if (this->count > 0)
    {
      gzmsg << this->count << " sec to turn on..." << std::endl;
    }
    else if (this->count == 0)
    {
      this->TurnOnAll();
      gzmsg << "Lights are on now." << std::endl;
    }
  }
}

// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(LightControlPlugin)
