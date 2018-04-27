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

Path thePathToSuccess;

void pathCallBack(const Path::ConstPtr& googlePath)
{
        thePathToSuccess = *googlePath;
        ROS_INFO("I am getting a Path! I think we are good to go");
}

int main(int argc, char* argv[])
{
        ros::init(argc, argv, "navigation_goals");
        ros::NodeHandle nh;

        ros::Subscriber pathListener = nh.subscribe("chatter", 10, pathCallBack);

        MoveBaseClient ac("move_base", true);
        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose.header.frame_id = "base_link";
        ROS_INFO("I am main here");
        for(int i = 0; i < thePathToSuccess.poses.size(); i++)
        {
                goal.target_pose.pose.position.x = thePathToSuccess.poses[i].pose.position.x;
                goal.target_pose.pose.position.y = thePathToSuccess.poses[i].pose.position.y;
                goal.target_pose.pose.position.z = thePathToSuccess.poses[i].pose.position.z;
        }
        ros::spin();


        return 0;
}
