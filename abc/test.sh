#!/bin/bash

# list=/opt/ros/kinetic/share/aw_launch/config/conf/tasks/suzhou_xiangcheng_all/litai_road.yaml

# list=/opt/ros/kinetic/share/aw_launch/config/conf/tasks/suzhou_xiangcheng_all/litai_road_bicycle.yaml

list=/opt/ros/kinetic/share/aw_launch/config/conf/tasks/pheonix_walmart/pheonix_walmart_night1.yaml

echo ${list}

# park_id=`grep -E -o "park_id .+" ${list} | cut -d ' ' -f4`
# route_id=`grep -E -o "route_id .+" ${list} | cut -d ' ' -f4`
# park_id=`grep -E -o "park_id.+" /opt/ros/kinetic/share/aw_launch/config/conf/tasks/pheonix_walmart/pheonix_walmart_night1.yaml  | rev | cut -d ' ' -f1 | rev`
park_id=`grep -E -o "park_id.+" ${list} | rev | cut -d ' ' -f1 | rev`
# route_id=`grep -E -o "route_id.+" /opt/ros/kinetic/share/aw_launch/config/conf/tasks/pheonix_walmart/pheonix_walmart_night1.yaml  | rev | cut -d ' ' -f1 | rev`
route_id=`grep -E -o "route_id.+" ${list} | rev | cut -d ' ' -f1 | rev`
echo $park_id
echo $route_id
jsonname=${park_id}_${route_id}
echo -e "\033[32m${jsonname}\033[0m"
