contract Demo {

    function max(uint a, uint b)
    public
    returns(uint)
    {
        if(a > b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

}