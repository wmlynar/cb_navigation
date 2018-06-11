#!/usr/bin/env python

import sys
import rospy
import roslib; roslib.load_manifest('code_profiler')
from code_profiler.msg import Statistics

import numpy

class LiveProfile:

    agg_length = 1 # second

    agg = {}
    start_agg = None
        
    def __init__(self):
        rospy.init_node('liveprofile', anonymous=True)

        self.start_agg = rospy.get_rostime()

        args = sys.argv
        if len(args) < 2:
            print 'usage: ' + args[0] + ' topicname'
            exit()

        rospy.Subscriber(args[1], Statistics, self.callback)
        rospy.spin()

    def callback(self, data):
        now = rospy.get_rostime()
        diff = now - self.start_agg
        if diff.to_sec() > self.agg_length:
            self.report(self.agg)            
            self.start_agg = now
            self.agg = {}
        else:
            for l, t in zip(data.labels, data.time_secs):
                if l not in self.agg:
                    self.agg[l] = []
                self.agg[l].append(t)

    def report(self, data):
        for k, v in sorted(data.iteritems()):
            mean = "{0:.3f} ms".format(numpy.mean(v, axis=0)*1000)
            std  = "{0:.3f} ms".format(numpy.std(v, axis=0)*1000)
            print k.ljust(55), '\tmean: ', mean, '\tstd:', std, '\t (', len(v), ' samples)'
        
if __name__ == '__main__':
    LiveProfile()
