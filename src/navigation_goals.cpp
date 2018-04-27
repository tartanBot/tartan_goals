#include<ros/ros.h>
#include<move_base_msgs/MoveBaseAction.h>
#include<actionlib/client/simple_action_client.h>
#include<nav_msgs/Path.h>
#include<geometry_msgs/PoseStamped.h>
#include<iostream>

using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef nav_msgs::Path Path;
typedef geometry_msgs::PoseStamped PoseStamped;

PoseStamped goalPoseInPath;

void pathCallBack(const Path::ConstPtr& googlePath)
{
        cout << googlePath->poses.size() << endl;
        /*
         *for(int i = 0; i < googlePath->poses.size(); ++i)
         *{
         *}
         */
}

int main(int argc, char* argv[])
{
        ros::init(argc, argv, "navigation_goals");
        ros::NodeHandle nh;

        ros::Subscriber pathListener = nh.subscribe("chatter1", 1, pathCallBack);

        MoveBaseClient ac("move_base", true);
        while(!ac.waitForServer(ros::Duration(5.0))){
                ROS_INFO("Waiting for the move_base action server to come up");
        }

        while(ros::ok())
        {
                ROS_INFO("Hi There \n");
        }
        return 0;
}
