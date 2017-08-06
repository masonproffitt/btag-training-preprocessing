import h5py
from sklearn.metrics import roc_curve
import matplotlib.pyplot as plt

f = h5py.File('output.h5',  'r')
fpr, tpr, _ = roc_curve(f['jet']['particle_id'], f['jet']['rnnip_pb'], 5)
f.close()
plt.plot(tpr, 1 - fpr)
plt.title('ROC curve for RNNIP b-tagging')
plt.ylabel('Background rejection')
plt.xlabel('Signal efficiency')
plt.savefig('roccurve.png')
