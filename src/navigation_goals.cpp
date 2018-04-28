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


void pathCallBack(const Path::ConstPtr& googlePath)
{
        ROS_INFO("I am getting a Path! I think we are good to go");

        MoveBaseClient ac("move_base", true);

        while(!ac.waitForServer(ros::Duration(5.0)))
        {
                ROS_INFO("Waiting for move_base action server to come up");
        }

        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose.header.frame_id = "base_link";
        cout << "I am entering loop " << endl;
        for(int i = 0; i < googlePath->poses.size(); i++)
        {
                goal.target_pose.pose.position.x = googlePath->poses[i].pose.position.x;
                goal.target_pose.pose.position.y = googlePath->poses[i].pose.position.y;
                goal.target_pose.pose.position.z = googlePath->poses[i].pose.position.z;
                cout << i << endl;

                ROS_INFO("Sending goal %d", i);
                ac.sendGoal(goal);
                ac.waitForResult();

                if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                        ROS_INFO("Have reached waypoint %d ", i);
                else 
                        ROS_INFO("Well, tough luck! Some goals are unacheivable! ");

        }
}

int main(int argc, char* argv[])
{
        ros::init(argc, argv, "navigation_goals");
        ros::NodeHandle nh;

        ros::Subscriber pathListener = nh.subscribe("chatter", 1, pathCallBack);

        ros::spin();


        return 0;
}
