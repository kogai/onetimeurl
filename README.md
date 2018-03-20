

# Build
```
npm run build
```

# Watch

```
npm run watch
```


# Editor
If you use `vscode`, Press `Windows + Shift + B` it will build automatically

# Google container registry

* docker build -t app .
* docker tag app gcr.io/onetimeurl-198513/app:v1
* gcloud docker -- push gcr.io/onetimeurl-198513/app:v1
* kubectl run app --image=gcr.io/onetimeurl-198513/app:v1 --port 3000

## Local registry

* docker tag onetimeurl/app:v1 localhost:5000/onetimeurl/app:v1
* docker push localhost:5000/onetimeurl/app:v1

# Kubernetess

* minikube start --vm-driver=kvm2
* minikube dashboard
* kubectl cluster-info [dump]
* kubectl get nodes
* kubectl (get|describe|logs|exec)
* export POD_NAME=$(kubectl get pods -o go-template --template '{{range .items}}{{.metadata.name}}{{"\n"}}{{end}}')
