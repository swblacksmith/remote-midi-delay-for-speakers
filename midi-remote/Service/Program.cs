using Service.Website;
using Topshelf;

namespace Service
{
    class Program
    {
        static void Main(string[] args)
        {
            HostFactory.Run(factory =>
            {
                // Provide the service's behavior using our custom
                //  ServiceHost class
                //
                factory.Service<ServiceHost>(service =>
                {
                    service.ConstructUsing(name => new ServiceHost());
                    service.WhenStarted(sh => sh.Start());
                    service.WhenShutdown(sh => sh.Shutdown());
                    service.WhenStopped(sh => sh.Stop());
                });

                // Now define some attributes of the service overall
                //
                factory.RunAsLocalSystem();

                // Provide the metadata to the service control
                //
                factory.SetServiceName("self-hosted-midi-remote-webservice");
                factory.SetDisplayName("Self-hosted MIDI Remote webservice");
                factory.SetDescription("Self-hosted service for providing interface to local MIDI devices");

            });
        }
    }
}
