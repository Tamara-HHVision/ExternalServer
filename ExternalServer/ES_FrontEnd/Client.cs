namespace ES_FrontEnd
{
    public enum EClientType
    {
        VESSEL,
        PEDESTRIAN,
        VR,
        OPENSCENARIO,
    }


    public class Client
    {
        public int ID { get; set; }
        public string IP { get; set; }
        public int ClientCommandPort { get; set; }
        public int ClientDataPort { get; set; }
        public EClientType ClientType { get; set; }


        public Client(int _id, string _ip, int _commandPort, int _dataPort, EClientType _type)
        {
            ID = _id;
            IP = _ip;
            ClientCommandPort = _commandPort;
            ClientDataPort = _dataPort;
            ClientType = _type;
        }
    }
}
