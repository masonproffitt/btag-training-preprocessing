import h5py
from sklearn.metrics import roc_curve
import matplotlib.pyplot as plt

f = h5py.File('output.h5',  'r')
cfpr, ctpr, _ = roc_curve(f['jet']['PartonTruthLabelID'], f['jet']['rnnip_pc'], 4)
bfpr, btpr, _ = roc_curve(f['jet']['PartonTruthLabelID'], f['jet']['rnnip_pb'], 5)
f.close()
plt.title('ROC curves for RNNIP flavour tagging')
plt.ylabel('Background rejection')
plt.xlabel('Signal efficiency')
plt.plot(ctpr, 1 - cfpr, label='c jets')
plt.plot(btpr, 1 - bfpr, label='b jets')
plt.legend(loc='lower left')
plt.savefig('roccurves.png', transparent=True)
