contract Math {

    function calc(uint a, uint b)
    public
    returns(uint)
    {
        uint c = a * b + 10;
        return c;
    }

}