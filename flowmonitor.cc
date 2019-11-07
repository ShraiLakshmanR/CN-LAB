
#include"ns3/core-module.h"
#include"ns3/network-module.h"
#include"ns3/csma-module.h"
#include"ns3/internet-module.h"
#include"ns3/point-to-point-module.h"
#include"ns3/applications-module.h"
#include"ns3/ipv4-global-routing-helper.h"
#include"ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("NS3ScriptExample");

int main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

NodeContainer nodes;
nodes.Create(2);

PointToPointHelper pointToPoint;
pointToPoint.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
pointToPoint.SetChannelAttribute("Delay",StringValue("2ms"));

NetDeviceContainer devices;
devices=pointToPoint.Install(nodes);

InternetStackHelper stack;
stack.Install(nodes);

Ipv4AddressHelper address;
address.SetBase("10.1.1.0","255.255.255.0");

Ipv4InterfaceContainer interfaces = address.Assign (devices);

UdpEchoServerHelper echoServer (9);

 
ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
serverApps.Start(Seconds(1.0));
serverApps.Stop(Seconds(10.0));

UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
echoClient.SetAttribute("MaxPackets",UintegerValue(1));
echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
echoClient.SetAttribute("PacketSize",UintegerValue(1024));

ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
clientApps.Start(Seconds(2.0));
clientApps.Stop(Seconds(10.0));

FlowMonitorHelper flowmon;
Ptr<FlowMonitor>monitor=flowmon.InstallAll();
 
NS_LOG_INFO("Run Simulation");
Simulator::Stop(Seconds(11.0));
Simulator::Run ();

monitor->CheckForLostPackets();
Ptr<Ipv4FlowClassifier>classifier=DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier());

std::map<FlowId,FlowMonitor::FlowStats>stats=monitor->GetFlowStats();

for(std::map<FlowId,FlowMonitor::FlowStats>::const_iterator i=stats.begin();i!=stats.end();++i)
{
Ipv4FlowClassifier::FiveTuple t=classifier->FindFlow(i->first);
std::cout<<"Flow:"<<i->first<<"\nSourceAddress="<<t.sourceAddress<<" DestinationAddress="<<t.destinationAddress<<" Source Port:"<<t.sourcePort<<" "<<" Destination Port:"<<t.destinationPort<<"\n";
std::cout<<"Flow"<<i->first<<"("<<t.sourceAddress<<"->"<<t.destinationAddress<<")\n";

std::cout<<"TxBytes:"<<i->second.txBytes<<"\n";
std::cout<<"RxBytes:"<<i->second.rxBytes<<"\n";
std::cout<<"TxPackets:"<<i->second.txPackets<<"\n";
std::cout<<"RxPackets:"<<i->second.rxPackets<<"\n";
std::cout<<"Total time taken for the transmission"<<i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstTxPacket.GetSeconds()<<std::endl;

std::cout<<"Throughput:"<<i->second.rxBytes*8.0/(i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstTxPacket.GetSeconds())/1000/1000<<"mbps\n";
}

Simulator::Destroy();
NS_LOG_INFO("Done");

return 0;
}
