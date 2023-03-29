/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "RKSVEP.h"
#include "worker.h"
#include "Buffer.h"
#include "BufferQueue.h"
#include "SvepType.h"

#include <map>
#include <queue>
#include <memory>

namespace android {

class RotateWorker : public Worker {
  public:
  RotateWorker();
  ~RotateWorker() override;

  int Init(int timeline_fd);
  void Queue(std::shared_ptr<SvepBackendContext> abCtx);

  protected:
  void Routine() override;
  // int WaitAllFence(std::shared_ptr<SvepBackendContext> abCtx);
  int SignalFinishFence(std::shared_ptr<SvepBackendContext> abCtx);
  int RotateMode(std::shared_ptr<SvepBackendContext> abCtx);
  int CalculateCostTime(std::shared_ptr<SvepBackendContext> abCtx);
  private:
  std::queue<std::shared_ptr<SvepBackendContext>> abCtxQueue_;
  char cFenceName_[50];
  int iTimelineFd_;
  int iTimeline_;
  int iCurrentTimeline_;

  long totalTime_;
  long lastAvgCostTime_;
  long avgCnt_;
};
} //namespace android