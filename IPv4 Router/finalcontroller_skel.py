# Final Skeleton
#
# Hints/Reminders from Lab 3:
#d
# To check the source and destination of an IP packet, you can use
# the header information... For example:
#
# ip_header = packet.find('ipv4')
#
# if ip_header.srcip == "1.1.1.1":
#   print "Packet is from 1.1.1.1"
#
# Important Note: the "is" comparison DOES NOT work for IP address
# comparisons in this way. You must use ==.
# 
# To send an OpenFlow Message telling a switch to send packets out a
# port, do the following, replacing <PORT> with the port number the 
# switch should send the packets out:
#
#    msg = of.ofp_flow_mod()
#    msg.match = of.ofp_match.from_packet(packet)
#    msg.idle_timeout = 30
#    msg.hard_timeout = 30
#
#    msg.actions.append(of.ofp_action_output(port = <PORT>))
#    msg.data = packet_in
#    self.connection.send(msg)
#
# To drop packets, simply omit the action.
#

from pox.core import core
import pox.openflow.libopenflow_01 as of

log = core.getLogger()

class Final (object):
  """
  A Firewall object is created for each switch that connects.
  A Connection object for that switch is passed to the __init__ function.
  """
  def __init__ (self, connection):
    # Keep track of the connection to the switch so that we can
    # send it messages!
    self.connection = connection

    # This binds our PacketIn event listener
    connection.addListeners(self)


  def do_final (self, packet, packet_in, port_on_switch, switch_id):
    # This is where you'll put your code. The following modifications have 
     # been made from Lab 3:
     #   - port_on_switch: represents the port that the packet was received on.
     #   - switch_id represents the id of the switch that received the packet.
     #      (for example, s1 would have switch_id == 1, s2 would have switch_id == 2, etc...)
     # You should use these to determine where a packet came from. To figure out where a packet 
     # is going, you can use the IP header information.
    
    def flood():
      """ Floods the packet """
      print("flood", packet_in)
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.idle_timeout = 20
      msg.hard_timeout = 40
      msg.buffer_id = packet_in.buffer_id
      msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
      self.connection.send(msg)

    def send(port):
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.idle_timeout = 20
      msg.hard_timeout = 40
      msg.actions.append(of.ofp_action_output(port = port))
      msg.data = packet_in
      self.connection.send(msg)


    def drop():
      """
      Drops this packet and optionally installs a flow to continue
      dropping similar ones for a while
      """
      print("drop", packet_in)
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.idle_timeout = 20
      msg.hard_timeout = 40
      msg.buffer_id = packet_in.buffer_id
      self.connection.send(msg)
    
    deptA = ["10.1.1.10", "10.1.2.20", "10.1.3.30", "10.1.4.40"]
    deptB = ["10.2.5.50", "10.2.6.60", "10.2.7.70", "10.2.8.80"]
    deptA1 = ["10.1.1.10", "10.1.2.20"]
    deptA2 = ["10.1.3.30", "10.1.4.40"]
    deptB1 = ["10.2.5.50", "10.2.6.60"]
    deptB2 = ["10.2.7.70", "10.2.8.80"]
    server = ["10.3.9.90"]
    trust = ["108.24.31.112"]
    untrust = ["106.44.82.103"]

    ip = packet.find('ipv4')
    icmp = packet.find('icmp')
    arp = packet.find('arp')

    if arp:
      flood()

    if ip:
      if switch_id == 11:
        print "from s11"
        if ip.dstip == "10.1.1.10":
          print ("to h10")
          send(1)
        elif ip.dstip == "10.1.2.20":
          print ("to h20")
          send(2)
        else:
          send(10)

      if switch_id == 12:
        print "from s12"
        if ip.dstip == "10.1.3.30":
          print ("to h30")
          send(3)
        elif ip.dstip == "10.1.4.40":
          print ("to h40")
          send(4)
        else:
          send(11)       
          
      if switch_id == 21:
        print "from s21"
        if ip.dstip == "10.2.5.50":
          print ("to h50")
          send(5)
        elif ip.dstip == "10.2.6.60":
          print ("to h60")
          send(6)
        else:
          send(12)

      if switch_id == 22: 
        print "from 22"
        if ip.dstip == "10.2.7.70":
          print ("to h70")
          send(7)
        elif ip.dstip == "10.2.8.80":
          print ("to h80")
          send(8)
        else:
          send(13)       

      if switch_id == 6: #DataCenter
        print "from Data center Switch"
        if ip.dstip == "10.3.9.90":
          print ("to server")
          send(9)
        else:
          send(14)


      if switch_id == 5: #Core
        if packet.find('icmp'):
          if ip.srcip in untrust and (ip.dstip in deptA or ip.dstip in deptB or ip.dstip in server):
            drop()
            return
              
        if packet.find('ipv4'):
          if ip.srcip in untrust and ip.dstip in server:
            drop()
            return

        if packet.find('icmp'):
          if ip.srcip in trust and (ip.dstip in deptB or ip.dstip in server):
            drop()
            return
      
        if packet.find('ipv4'):
          if ip.srcip in trust and ip.dstip in server:
            drop()
            return

        if packet.find('icmp'):
          if ip.srcip in deptA and ip.dstip in deptB:
            drop()
            return

          if ip.srcip in deptB and ip.dstip in deptA:
            drop()
            return
        
        if ip.dstip in trust:
          print "To trusted"
          send(6)
          return
        
        if ip.dstip in untrust:
          print "To trusted"
          send(7)
          return

        if ip.dstip in deptA1:
          print "To floor 1 & switch 1"
          send(1)
          return

        if ip.dstip in deptA2:
          print "To floor 1 & switch 2"
          send(2)
          return

        if ip.dstip in deptB1:
          print "To floor 2 & switch 3"
          send(3)
          return

        if ip.dstip in deptB2:
          print "To floor 2 & switch 4"
          send(4)
          return

        if ip.dstip in server:
          print "To server through Data center switch"
          send(5)         
          return
     

          


  def _handle_PacketIn (self, event):
    packet = event.parsed # This is the parsed packet data.
    if not packet.parsed:
      log.warning("Ignoring incomplete packet")
      return
    packet_in = event.ofp # The actual ofp_packet_in message.
    self.do_final(packet, packet_in, event.port, event.dpid)

def launch ():
  """
  Starts the component
  """
  def start_switch (event):
    log.debug("Controlling %s" % (event.connection,))
    Final(event.connection)
  core.openflow.addListenerByName("ConnectionUp", start_switch)
