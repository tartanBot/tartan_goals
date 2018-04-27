#include<ros/ros.h>
#include<move_base_msgs/MoveBaseAction.h>
#include<actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
int main(int argc, char* argv[])
{
        ros::init(argc, argv, "navigation_goals");
        MoveBaseClient ac("move_base", true);

        while(!ac.waitForServer(ros::Duration(5.0)) && ros::ok())
        {
                ROS_INFO("Waiting for the move_base action server to come up");
        }

        move_base_msgs::MoveBaseGoal goal;

        while(ros::ok())
        {
                ROS_INFO("Hi There \n");
        }
        return 0;
}
