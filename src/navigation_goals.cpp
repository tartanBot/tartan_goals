#include<ros/ros.h>
#include<move_base_msgs/MoveBaseAction.h>
#include<actionlib/client/simple_action_client.h>
#include<nav_msgs/Path.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef nav_msgs::Path Path;


class listenPathAndPublishGoal
{
        private:
                move_base_msgs::MoveBaseGoal goal;
                ros::NodeHandle n;
                ros::Subscriber pathListener; 
        public:
                listenPathAndPublishGoal(MoveBaseClient mb_client)
                {
                }
};
int main(int argc, char* argv[])
{
        ros::init(argc, argv, "navigation_goals");
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
