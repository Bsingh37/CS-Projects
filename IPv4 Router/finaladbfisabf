#!/usr/bin/python

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.cli import CLI
from mininet.node import RemoteController

class final_topo(Topo):
  def build(self):
   ##host server
   h_server = self.addHost('h_server',mac='00:00:00:00:00:0A',ip='10.3.9.90/24',defaultRoute="h_server-eth0") ## Adds a Host
   h_trust = self.addHost('h_trust',mac='00:00:00:00:00:09',ip='108.24.31.112/24',defaultRoute="h_trust-eth0") ## Trusted
   h_untrust = self.addHost('h_untrust',mac='00:00:00:00:00:10',ip='106.44.82.103/24',defaultRoute="h_untrust-eth0") ## Untrusted

   #11 Topology
   h10 = self.addHost('h10',mac='00:00:00:00:00:01',ip='10.1.1.10/24',defaultRoute="h10-eth0") ## Adds a Host 
   h20 = self.addHost('h20',mac='00:00:00:00:00:02',ip='10.1.2.20/24',defaultRoute="h20-eth0") ## Adds a Host
  
   s11 = self.addSwitch('s11') ## Adds a Switch
   self.addLink(s11,h10, port1=1, port2=0) ## Add a link
   self.addLink(s11,h20, port1=2, port2=0) ## Add a link

   #12 Topology
   h30 = self.addHost('h30',mac='00:00:00:00:00:03',ip='10.1.3.30/24',defaultRoute="h30-eth0") ## Adds a Host
   h40 = self.addHost('h40',mac='00:00:00:00:00:04',ip='10.1.4.40/24',defaultRoute="h40-eth0") ## Adds a Host
  
   s12 = self.addSwitch('s12') ## Adds a Switch
   self.addLink(s12,h30, port1=3, port2=0) ## Add a link
   self.addLink(s12,h40, port1=4, port2=0) ## Add a link

   #21 Topology
   h50 = self.addHost('h50',mac='00:00:00:00:00:05',ip='10.2.5.50/24',defaultRoute="h50-eth0") ## Adds a Host
   h60 = self.addHost('h60',mac='00:00:00:00:00:06',ip='10.2.6.60/24',defaultRoute="h60-eth0") ## Adds a Host

   s21 = self.addSwitch('s21') ## Adds a Switch
   self.addLink(s21,h50, port1=5, port2=0) ## Add a link
   self.addLink(s21,h60, port1=6, port2=0) ## Add a link

   #22 Topology
   h70 = self.addHost('h70',mac='00:00:00:00:00:07',ip='10.2.7.70/24',defaultRoute="h70-eth0") ## Adds a Host
   h80 = self.addHost('h80',mac='00:00:00:00:00:08',ip='10.2.8.80/24',defaultRoute="h80-eth0") ## Adds a Host

   s22 = self.addSwitch('s22') ## Adds a Switch
   self.addLink(s22,h70, port1=7, port2=0) ## Add a link
   self.addLink(s22,h80, port1=8, port2=0) ## Add a link

   ##Miscellaneous
   s5 = self.addSwitch('s5') ## Core Switch
  
   s6 = self.addSwitch('s6') ## Data Center Switch

 
 
   ##Linking
   self.addLink(s6, h_server, port1=9, port2=0) ## s6 --> host server
   self.addLink(s11, s5, port1=10, port2=1) ## Switch1 --> Core Switch
   self.addLink(s12, s5, port1=11, port2=2) ## Switch2 --> Core Switch
   self.addLink(s21, s5, port1=12, port2=3) ## Switch3 --> Core Switch
   self.addLink(s22, s5, port1=13, port2=4) ## Switch4 --> Core Switch
   self.addLink(s6, s5, port1=14, port2=5) ## Core Switch --> s6
   self.addLink(h_trust, s5, port1=0, port2=6) ## trusted host --> Core Switch
   self.addLink(h_untrust, s5, port1=0, port2=7) ## Untrusted host --> Core Switch

def configure():
  topo = final_topo()
  net = Mininet(topo=topo, controller=RemoteController)
  net.start()

  CLI(net)
  
  net.stop()


if __name__ == '__main__':
  configure()
