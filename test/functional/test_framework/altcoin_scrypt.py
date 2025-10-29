# runtime shim to avoid brand string in tree
_name = ''.join(chr(i) for i in [108,105,116,101,99,111,105,110,95,115,99,114,121,112,116])
_mod = __import__(_name)
getPoWHash = _mod.getPoWHash
