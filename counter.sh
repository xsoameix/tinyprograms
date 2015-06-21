#!/bin/bash
STEP=1
info() {
  echo "Step $STEP : $1"
  STEP=$(($STEP+1))
}

info 'Stop'
info 'Prepare'
info 'Run'
