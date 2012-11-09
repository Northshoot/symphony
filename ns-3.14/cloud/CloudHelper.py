#!/usr/bin/python

#!/usr/bin/python

import os
import boto
import boto.ec2
import time
from boto.ec2.cloudwatch import MetricAlarm
import boto.ec2.cloudwatch

user = "lauril"
name = "experiment"
ami=""
instance_id=""
my_instance_type="c1.xlarge"
number_of_instances=10

class Connector():
    def __init__(self):
        self.connect()

    def connect(self):
        # Init needed connections
        self.conn = boto.ec2.connect_to_region('eu-west-1')


    def create_ami(self,instance_id,name,tags={}, num = 1):
        _id = self.conn.create_image(instance_id, '12_SYMPHONY_%s' % name)
        time.sleep(5)
        print 'AMI id = %s' % _id
        tags = dict(tags.items() + {'user':user, 'course':'admin', 'Name':'12_SYMPHONY_%s' % name}.items() )
        print tags
        self.conn.create_tags([_id], tags)
        time.sleep(60)
        self.launch_instances(_id, num = num, extra_tags=tags)

    def launch_instances(self, ami, num=number_of_instances, extra_tags = {}, instance_type = my_instance_type):
        # Launch one or more EC2 instances from AMI
        self.res = self.conn.run_instances(
            image_id=ami,
            key_name='12_SYMPHONY_%s' % user,
            instance_type=instance_type,
            security_groups=['12_SYMPHONY_%s' % user],
            min_count=num, max_count=num,monitoring_enabled=True,
            placement='eu-west-1a')

        time.sleep(5)
        # Tag instances
        for inst in self.res.instances:
            inst.add_tag('Name', '12_SYMPHONY_%s' % user)
            inst.add_tag('user', user)
            for key, value in extra_tags.items():
                inst.add_tag(key, value)






    def stop_all(self):
        self.stop_instances()
        self.stop_wsn()
        self.stop_gui()
        self.conn.close()
        time.sleep(10)

    def stop_instance(self, instance):
        if instance.state == u'running':
            instance.stop()
        instance.add_tag('Name', 'delete-me_%s' % user)
        instance.add_tag('action', 'delete')

    def stop_instances(self, instance = None):
        print 'Stop instances'
        # Stop all of my running instances and mark for deletion
        for r in self.conn.get_all_instances(filters={'tag-value':user}):
            for i in r.instances:
                self.stop_instance(i)
        time.sleep(10)

    def get_instances(self, input_filter={}):
        instances = []
        for r in self.conn.get_all_instances(filters=dict({'tag-value':user}.items() + input_filter.items())):
            for i in r.instances:
                if i.state == u'running':
                    instances.append(i)
        return instances

    def get_instance(self, instance_id):
        for r in self.conn.get_all_instances([instance_id]):
            for i in r.instances:
                return i



    def get_ami(self, input_filter):
        for ami in self.conn.get_all_images(filters=dict({'tag-value':user}.items() + input_filter.items())):
            return ami.id




if __name__ == '__main__':
    c = Connector()
    print 'starting wsn'
    c.start_wsn()
    print 'starting gui'
    c.start_gui()
    print 'sleep 60sek'
    time.sleep(60)
    c.print_ip()
    #time.sleep(10)
    #c.upload_code()
