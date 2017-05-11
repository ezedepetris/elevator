ELEVATOR
--------
project for subject "simulation 2016" made it on powerdevs

Developers: Depetris - Massimino

Scripts

**diff betwen two arrays**

```rb
def diff(ar1, ar2)
  ar3 = []
  ar1.each_with_index do |a, i|
    ar3[i] = (ar2[i]-ar1[i]).to_d.truncate(2).to_f
  end
  ar3
end
```

**merge two arrays and sort the result**

```rb
def sort(ar1, ar2)
  ar3 = []
  ar3 = (ar2 << ar1).flatten
  ar3.sort
end
```

