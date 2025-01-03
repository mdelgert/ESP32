# Still not showing images correctly need to look into this

```bash
sudo apt install python3-virtualenv
python3 -m virtualenv .env
source .env/bin/activate
pip install -r requirements.txt
sudo apt install graphicsmagick-imagemagick-compat
convert key160X80.png -depth 16 -size 160x80 rgb:image.raw
python3 RawToArrary.py
```
